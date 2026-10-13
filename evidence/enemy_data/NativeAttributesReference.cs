using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Web.Script.Serialization;

// Source-owned reference for the static reconstruction. It is never linked to,
// loaded into, or run against GameAssembly. Host .NET is not a game oracle.
public static class NativeAttributesReference {
  static long SingleFP(float f) {
    double value=(double)f*4294967296.0;
    if(Double.IsNaN(value)||Double.IsInfinity(value)||value < -9223372036854775808.0||value>=9223372036854775808.0)
      return Int64.MinValue;
    return (long)Math.Truncate(value);
  }
  static int SingleInt(float value) {
    double rounded=Math.Round((double)value,MidpointRounding.ToEven);
    if(rounded < Int32.MinValue || rounded > Int32.MaxValue) return Int32.MinValue;
    return (int)rounded;
  }
  public static void Main(string[] args) {
    var serializer=new JavaScriptSerializer();
    serializer.MaxJsonLength=10000000;
    var input=serializer.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
    var output=new List<Dictionary<string,object>>();
    foreach(Dictionary<string,object> row in (ArrayList)input["cases"]) {
      string mode=(string)row["mode"];
      float single;
      if(mode=="write_fp") single=(float)Convert.ToInt64(row["fp_raw"])*(1.0f/4294967296.0f);
      else single=(float)Convert.ToDouble(row["value"]);
      object decoded=(bool)row["integer"] ? (object)SingleInt(single) : (object)single;
      long fp=SingleFP((float)Convert.ToDouble(decoded));
      long min=Convert.ToInt64(row["min_raw"]),max=Convert.ToInt64(row["max_raw"]);
      long clamped=Math.Max(min,Math.Min(fp,max));
      output.Add(new Dictionary<string,object>{{"id",row["id"]},{"decoded",decoded},
        {"decoded_single_bits",BitConverter.ToUInt32(BitConverter.GetBytes((float)Convert.ToDouble(decoded)),0)},
        {"unclamped_raw",fp},{"clamped_raw",clamped}});
    }
    Console.Write(serializer.Serialize(new Dictionary<string,object>{{"reference_kind","static reconstruction; no client runtime oracle"},{"cases",output}}));
  }
}
