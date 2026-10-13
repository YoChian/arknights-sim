// Source-owned C# translation. Not a native/client oracle; no game is loaded.
// Div/LeadingZeroes reuse the independently validated FPReference.cs algorithm
// (SHA ec50d0338883c6a4eb690d6da1fa7bedcc2b5cc58eaa5c10a12058014f126ec6).
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Web.Script.Serialization;

class TargetingRuntimeReference {
    const long One=1L<<32,Gap=4294967,Big=1000000L<<32,Epsilon=42950;
    static object[] A(object o) { return o is ArrayList?((ArrayList)o).ToArray():(object[])o; }
    static Dictionary<string,object> D(object o) { return (Dictionary<string,object>)o; }
    static long L(object o) { return long.Parse(Convert.ToString(o),System.Globalization.CultureInfo.InvariantCulture); }
    static uint U(object o) { return Convert.ToUInt32(o); }
    static int I(object o) { return Convert.ToInt32(o); }
    static bool B(object o) { return Convert.ToBoolean(o); }
    static long Abs(long a) { return a==long.MinValue?long.MaxValue-1:Math.Abs(a); }
    static long Floor(long a) { return (a>>32)<<32; }
    static bool Eq(long a,long b) { return Abs(unchecked(a-b))<Epsilon; }
    static int LeadingZeroes(ulong x) {
        int n=0;
        while((x&0xF000000000000000UL)==0) { n+=4;x<<=4; }
        while((long)x>=0) { ++n;x<<=1; }
        return n;
    }
    static long Div(long x,long y) {
        if(y==0)return -One;
        unchecked {
            ulong rem=(ulong)(x<0?-x:x),divider=(ulong)(y<0?-y:y),q=0;
            int bit=33;
            while((divider&15)==0 && bit>3) { divider>>=4;bit-=4; }
            while(rem!=0 && bit>=0) {
                int shift=Math.Min(LeadingZeroes(rem),bit);
                rem<<=shift;bit-=shift;
                ulong part=rem/divider;q+=part<<bit;
                if((part&~(ulong.MaxValue>>bit))!=0)return (x^y)<0?long.MinValue+2:long.MaxValue-1;
                rem=(rem%divider)<<1;--bit;
            }
            long result=(long)((q+1)>>1);
            return (x^y)<0?-result:result;
        }
    }
    static int Compare(uint uid,long a,uint other,long b) {
        long x=a,y=b;
        if(Abs(a)>Big && Abs(b)>Big) {
            long fa=Floor(a),fb=Floor(b);
            if(Eq(fa,fb)) { x=Floor(Div(unchecked(a-fa),Gap));y=Floor(Div(unchecked(b-fb),Gap)); }
            else { x=fa;y=fb; }
        } else if(Abs(a)<Big && Abs(b)<Big) {
            x=Floor(Div(a,Gap));y=Floor(Div(b,Gap));
        }
        return Eq(x,y)?uid.CompareTo(other):x.CompareTo(y);
    }
    static object Queue(Dictionary<string,object> row) {
        var list=new List<Tuple<uint,long>>();var kept=new List<uint>();var dropped=new List<uint>();
        foreach(object raw in A(row["items"])) {
            var e=D(raw);uint uid=U(e["uid"]);
            if(!B(e["alive"])) { dropped.Add(uid);continue; }
            kept.Add(uid);long value=L(e["raw"]);int i=0;
            while(i<list.Count && Compare(uid,value,list[i].Item1,list[i].Item2)>0)i++;
            list.Insert(i,Tuple.Create(uid,value));
        }
        var order=new List<uint>();foreach(var x in list)order.Add(x.Item1);
        return new Dictionary<string,object>{{"id",row["id"]},{"order",order},{"kept",kept},{"dropped",dropped}};
    }
    static object Status(Dictionary<string,object> row) {
        int flag=I(row["flag"]),active=I(row["active"]),immune=I(row["immune"]);
        ulong bits=ulong.Parse((string)row["base_bits"]);
        long selected=unchecked((long)(bits&(1UL<<(flag&63))));
        bool value=immune<=0 && active>0 || selected>0;
        return new Dictionary<string,object>{{"id",row["id"]},{"flag",value},{"immune",immune>0}};
    }
    static int Same(int side) { int[] v={1,2,4};for(int i=0;i<3;i++)if(side==(1<<i))return v[i];return side; }
    static int Opp(int side) { int[] v={2,5,2};for(int i=0;i<3;i++)if(side==(1<<i))return v[i];return 0; }
    static int ConvertSide(int side,int target) {
        if(side==0)return target;
        if(target==1)return Same(side);if(target==2)return Opp(side);
        if(target==3)return Same(side)|Opp(side);return 7;
    }
    public static void Main(string[] args) {
        var j=new JavaScriptSerializer();j.MaxJsonLength=Int32.MaxValue;
        var input=D(j.DeserializeObject(File.ReadAllText(args[0])));
        var comparisons=new List<object>();var queues=new List<object>();var statuses=new List<object>();var masks=new List<object>();
        foreach(object raw in A(input["comparisons"])) {
            var row=D(raw);
            comparisons.Add(new Dictionary<string,object>{{"id",row["id"]},
                {"comparison",Compare(U(row["uid"]),L(row["raw"]),U(row["other_uid"]),L(row["other_raw"]))}});
        }
        foreach(object raw in A(input["queues"]))queues.Add(Queue(D(raw)));
        foreach(object raw in A(input["statuses"]))statuses.Add(Status(D(raw)));
        for(int side=0;side<8;side++)for(int target=0;target<8;target++) {
            int abs=ConvertSide(side,target),mask=0;
            if((abs&1)!=0)mask|=1<<10;if((abs&2)!=0)mask|=1<<9;if((abs&4)!=0)mask|=1<<28;
            masks.Add(new int[]{side,target,abs,mask});
        }
        var result=new Dictionary<string,object>{{"scope","independent C# native-rule translation; no Unity/physics/client execution"},
            {"comparisons",comparisons},{"queues",queues},{"statuses",statuses},{"masks",masks}};
        File.WriteAllText(args[1],j.Serialize(result),new System.Text.UTF8Encoding(false));
    }
}
