// Independent source-owned translation of recovered bounded branches.
// This program does not load Unity/the game and is not a client oracle.
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Web.Script.Serialization;

public static class TargetingReference {
    static Dictionary<string,object> Obj(object o) { return (Dictionary<string,object>)o; }
    static object[] Arr(object o) {
        if(o is object[])return (object[])o;
        if(o is ArrayList)return ((ArrayList)o).ToArray();
        throw new ArgumentException("JSON array required: "+o.GetType().FullName);
    }
    static int I(object o) { return Convert.ToInt32(o); }
    static uint U(object o) { return Convert.ToUInt32(o); }
    static bool B(object o) { return Convert.ToBoolean(o); }
    // Force each recovered Single operation through a binary32 bit roundtrip.
    static float F(double x) { return BitConverter.ToSingle(BitConverter.GetBytes((float)x),0); }
    static int Bits(float x) { return BitConverter.ToInt32(BitConverter.GetBytes(x),0); }
    struct Cell : IEquatable<Cell> {
        public int r,c;
        public Cell(int row,int col) { r=row;c=col; }
        public bool Equals(Cell x) { return r==x.r && c==x.c; }
        public override bool Equals(object x) { return x is Cell && Equals((Cell)x); }
        public override int GetHashCode() { return unchecked(r*65537+c); }
    }
    static Cell Rotate(Cell p,int current) {
        switch ((4-current)%4) {
            case 0:return p;
            case 1:return new Cell(-p.c,p.r);
            case 2:return new Cell(-p.r,-p.c);
            default:return new Cell(p.c,-p.r);
        }
    }
    static object Geometry(Dictionary<string,object> x) {
        var cells=new List<Cell>();
        foreach(object raw in Arr(x["grids"])) {
            object[] v=Arr(raw); cells.Add(Rotate(new Cell(I(v[0]),I(v[1])),I(x["direction"])));
        }
        cells.Sort(delegate(Cell a,Cell b) { return a.r==b.r?a.c-b.c:a.r-b.r; });
        var all=new HashSet<Cell>(cells); var pending=new HashSet<Cell>(cells);
        var boxes=new List<object>();
        foreach(Cell start in cells) {
            if(!pending.Remove(start))continue;
            int endC=start.c,endR=start.r;
            while(all.Contains(new Cell(start.r,endC+1))) {
                endC++; pending.Remove(new Cell(start.r,endC));
            }
            while(true) {
                bool valid=true;
                for(int c=start.c;c<=endC;c++)if(!all.Contains(new Cell(endR+1,c))) { valid=false;break; }
                if(!valid)break;
                endR++;
                for(int c=start.c;c<=endC;c++)pending.Remove(new Cell(endR,c));
            }
            float minX=F(start.c-.5),minY=F(start.r-.5);
            float sizeX=F(endC-start.c+1),sizeY=F(endR-start.r+1);
            float centerX=F(F(sizeX*F(.5))+minX),centerY=F(F(sizeY*F(.5))+minY);
            boxes.Add(new int[]{Bits(minX),Bits(minY),Bits(sizeX),Bits(sizeY),Bits(centerX),Bits(centerY)});
        }
        return new Dictionary<string,object>{{"id",x["id"]},{"box_bits",boxes}};
    }
    static string Admission(Dictionary<string,object> t,Dictionary<string,object> c) {
        if((3 & (1<<I(t["motion"])))==0)return "motion_mask";
        if((1 & I(t["category"]))==0)return "category_mask";
        if(I(c["source_side"])!=0 && I(t["side"])==I(c["source_side"]) && B(t["ally_target_free"]))return "ally_target_free";
        if((I(c["source_purpose_mask"])&2)!=0 && B(t["heal_free"]))return "heal_free";
        if(I(t["map_layer"])!=I(c["source_map_layer"]))return "map_layer";
        if(!B(t["hit_range"]))return "hit_range_provider";
        if(!B(c["ability_ignores_camouflage"]) && B(t["camouflage"]) &&
            (I(t["side"])&I(c["opposite_side_mask"]))==I(t["side"]))return "enemy_camouflage";
        if(B(c["has_custom_validator"]) && !B(t["custom_validator"]))return "custom_validator";
        if(B(t["excluded"]))return "advanced_exclusion_set";
        return null;
    }
    static object Collect(Dictionary<string,object> x) {
        var context=Obj(x["context"]);
        var selected=new List<uint>(); var seen=new HashSet<uint>(); var decisions=new List<object>();
        bool cap=false; int ci=0;
        foreach(object rawC in Arr(x["colliders"])) {
            var col=Obj(rawC);
            if(B(col["destroyed"])) {
                decisions.Add(new object[]{ci,null,null,"range_collider_destroyed"});ci++;continue;
            }
            int hi=0;
            foreach(object rawT in Arr(col["hits"])) {
                string reason=null; object uid=null;
                if(rawT==null)reason="collider_has_no_live_entity";
                else {
                    var t=Obj(rawT); uint u=U(t["uid"]); uid=u;
                    if(B(t["destroyed"]))reason="entity_destroyed";
                    else if(u==0)reason="instance_uid_invalid";
                    else if(!B(t["alive"]))reason="entity_not_alive";
                    else if(seen.Contains(u))reason="duplicate_admitted_uid";
                    else reason=Admission(t,context);
                    if(reason==null) { selected.Add(u);seen.Add(u); }
                }
                decisions.Add(new object[]{ci,hi,uid,reason??"admitted"});hi++;
                if(selected.Count>=128) { cap=true;break; }
            }
            if(cap)break;
            ci++;
        }
        if(B(context["deterministic"]))selected.Sort(); // UInt32, unique admitted UID keys
        uint[] collector=selected.ToArray();selected.Reverse(); // Explicit test ALL permutation, not native ALL.
        return new Dictionary<string,object>{{"id",x["id"]},{"collector",collector},
            {"fixture_all_output",selected},{"decisions",decisions},{"capped",cap}};
    }
    public static void Main(string[] args) {
        var serializer=new JavaScriptSerializer();serializer.MaxJsonLength=Int32.MaxValue;
        var input=serializer.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
        var geometry=new List<object>();var collectors=new List<object>();
        foreach(object x in Arr(input["geometry"]))geometry.Add(Geometry(Obj(x)));
        foreach(object x in Arr(input["collectors"]))collectors.Add(Collect(Obj(x)));
        var output=new Dictionary<string,object>{{"scope","independent reconstructed C# bounded geometry/collector; supplied physics/status and fixture ALL reversal; not a native/client oracle"},
            {"geometry",geometry},{"collectors",collectors}};
        File.WriteAllText(args[1],serializer.Serialize(output),new System.Text.UTF8Encoding(false));
    }
}
