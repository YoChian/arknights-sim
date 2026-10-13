using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Numerics;
using System.Web.Script.Serialization;

// Independent source-owned arithmetic reference, without game assemblies.
// BigInteger explicitly represents the full signed product and low 64 bits.
public static class NativeDamageReference {
  static long Signed64(BigInteger value) {
    BigInteger bits = value & ((BigInteger.One << 64) - 1);
    if(bits >= (BigInteger.One << 63)) bits -= (BigInteger.One << 64);
    return (long)bits;
  }
  public static void Main(string[] args) {
    var serializer = new JavaScriptSerializer();
    serializer.MaxJsonLength = 10000000;
    var input = serializer.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
    var output = new List<Dictionary<string,object>>();
    foreach(Dictionary<string,object> row in (ArrayList)input["cases"]) {
      long attack=Convert.ToInt64(row["attack_raw"]), scale=Convert.ToInt64(row["scale_raw"]);
      long hp=Convert.ToInt64(row["hp_raw"]), max=Convert.ToInt64(row["max_hp_raw"]);
      BigInteger product=(new BigInteger(attack)*new BigInteger(scale))>>32;
      long damage=Math.Max(0,Signed64(product));
      long requested=Signed64(new BigInteger(hp)-new BigInteger(damage));
      long written=Math.Min(max,Math.Max(0,requested));
      if(written<42950) written=0;
      output.Add(new Dictionary<string,object>{{"id",row["id"]},{"damage_raw",damage},
        {"written_hp_raw",written},{"applied_delta_raw",Signed64(new BigInteger(written)-new BigInteger(hp))},
        {"killed",written==0}});
    }
    Console.Write(serializer.Serialize(new Dictionary<string,object>{{"reference_kind","source-owned BigInteger reconstruction; no client runtime oracle"},{"cases",output}}));
  }
}
