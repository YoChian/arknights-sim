// Source-owned C# scalar query-argument translation, not a Unity/client oracle.
// No physics engine, Unity assembly, transformed pose or overlap is computed.
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Web.Script.Serialization;

class PhysicsContextReference {
    static object[] A(object value) {return value is ArrayList?((ArrayList)value).ToArray():(object[])value;}
    static Dictionary<string,object> D(object value) {return (Dictionary<string,object>)value;}
    static float F(object value) {uint bits=Convert.ToUInt32(((string)value).Substring(2),16);return BitConverter.ToSingle(BitConverter.GetBytes(bits),0);}
    static string Bits(float value) {return "0x"+BitConverter.ToUInt32(BitConverter.GetBytes(value),0).ToString("x8");}
    static float S(double value) {return BitConverter.ToSingle(BitConverter.GetBytes((float)value),0);}
    static float[] Vector(object value) {object[] raw=A(value);float[] output=new float[raw.Length];for(int i=0;i<raw.Length;i++)output[i]=F(raw[i]);return output;}
    static string[] BitVector(float[] value) {string[] output=new string[value.Length];for(int i=0;i<value.Length;i++)output[i]=Bits(value[i]);return output;}
    static bool Finite(float value) {return !Single.IsNaN(value)&&!Single.IsInfinity(value);}
    static bool Scope(float value) {return Finite(value)&&(value==0||Math.Abs(value)>=1.1754943508222875e-38F);}
    static object Box(Dictionary<string,object> row) {
        float[] ca=Vector(row["minimum_center"]),ea=Vector(row["minimum_extents"]);
        float[] cb=Vector(row["maximum_center"]),eb=Vector(row["maximum_extents"]);
        float[] a=new float[3],b=new float[3],c=new float[2],s=new float[2];bool finite=true;
        for(int i=0;i<3;i++){a[i]=S((double)ca[i]-ea[i]);b[i]=S((double)cb[i]+eb[i]);finite&=Scope(ca[i])&&Scope(ea[i])&&Scope(cb[i])&&Scope(eb[i])&&Scope(a[i])&&Scope(b[i]);}
        for(int i=0;i<2;i++){float sum=S((double)a[i]+b[i]),delta=S((double)a[i]-b[i]);c[i]=S((double)sum*.5);s[i]=Math.Abs(delta);finite&=Scope(sum)&&Scope(delta)&&Scope(c[i])&&Scope(s[i]);}
        return new Dictionary<string,object>{{"id",row["id"]},{"finite_scope",finite},{"minimum",BitVector(a)},{"maximum",BitVector(b)},
            {"box_center",BitVector(c)},{"box_size",BitVector(s)},{"angle","0x00000000"}};
    }
    static object Radius(Dictionary<string,object> row) {
        float[] v=Vector(row["transformed_radius_vector"]);
        float x=S((double)v[0]*v[0]),y=S((double)v[1]*v[1]),z=S((double)v[2]*v[2]);
        float sum=S((double)S((double)x+y)+z);float radius=S(Math.Sqrt((double)sum));
        return new Dictionary<string,object>{{"id",row["id"]},{"finite_scope",Scope(v[0])&&Scope(v[1])&&Scope(v[2])&&Scope(x)&&Scope(y)&&Scope(z)&&Scope(S((double)x+y))&&Scope(sum)&&Scope(radius)},{"radius",Bits(radius)}};
    }
    static object Filter(Dictionary<string,object> row) {
        byte[] value=new byte[28];value[0]=Convert.ToBoolean(row["queries_hit_triggers"])?(byte)1:(byte)0;value[1]=value[2]=1;
        Array.Copy(BitConverter.GetBytes(Convert.ToInt32(row["layer_mask"])),0,value,8,4);
        Array.Copy(BitConverter.GetBytes(Single.NegativeInfinity),0,value,12,4);Array.Copy(BitConverter.GetBytes(Single.PositiveInfinity),0,value,16,4);
        return new Dictionary<string,object>{{"id",row["id"]},{"initial_filter_hex",BitConverter.ToString(value).Replace("-","").ToLowerInvariant()}};
    }
    public static void Main(string[] args) {
        var json=new JavaScriptSerializer();json.MaxJsonLength=Int32.MaxValue;
        var input=D(json.DeserializeObject(File.ReadAllText(args[0])));var boxes=new List<object>();var radii=new List<object>();var filters=new List<object>();
        foreach(object value in A(input["boxes"]))boxes.Add(Box(D(value)));
        foreach(object value in A(input["radii"]))radii.Add(Radius(D(value)));
        foreach(object value in A(input["filters"]))filters.Add(Filter(D(value)));
        var modes=new List<object>();for(int mode=0;mode<=2;mode++)modes.Add(new int[]{mode,mode!=2?1:0,mode==2?1:0});
        var output=new Dictionary<string,object>{{"scope","separate C# scalar native-rule translation; external pose/filter/overlap remain external; no Unity/client execution"},
            {"boxes",boxes},{"radii",radii},{"filters",filters},{"simulation_modes",modes}};
        File.WriteAllText(args[1],json.Serialize(output),new System.Text.UTF8Encoding(false));
    }
}
