using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Web.Script.Serialization;

// Independent, source-owned numerical reference. No game assembly is loaded.
// This tests a static reconstruction; host .NET is not a client oracle.
public static class NativeLifecycleReference {
  public static void Main(string[] args) {
    var serializer = new JavaScriptSerializer();
    serializer.MaxJsonLength = 10000000;
    var input = serializer.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
    var result = new List<Dictionary<string,object>>();
    foreach (Dictionary<string,object> row in (ArrayList)input["cases"]) {
      string mode = (string)row["mode"];
      var expected = new Dictionary<string,object>();
      if (mode == "life") {
        int life = Convert.ToInt32(row["life"]), temp = Convert.ToInt32(row["temp"]);
        int delta = Convert.ToInt32(row["delta"]);
        bool tempGrant = delta > 0 && (bool)row["to_temp"];
        int grantedTemp = tempGrant ? checked(temp + delta) : temp;
        int permanentCandidate = tempGrant ? 0 : delta;
        int absorbed = Math.Min(grantedTemp, Math.Max(0, -permanentCandidate));
        int remainingTemp = grantedTemp - absorbed;
        int remainingLife = Math.Max(0, checked(life + permanentCandidate + absorbed));
        expected["life"] = remainingLife;
        expected["temp"] = remainingTemp;
        expected["applied_delta"] = remainingLife - life;
        expected["lost"] = remainingLife == 0;
      } else if (mode == "alive") {
        int state = Convert.ToInt32(row["state"]);
        long hp = Convert.ToInt64(row["hp_raw"]);
        expected["alive"] = state > 0 && state <= 16 && hp > 42950;
      } else if (mode == "birth") {
        float delay = Convert.ToSingle(row["delay"]);
        long dt = Convert.ToInt64(row["dt_raw"]);
        long remaining = delay > 0.00001f ? (long)Math.Truncate((double)delay * 4294967296.0) : 0;
        expected["remaining_raw"] = remaining;
        expected["frames"] = Math.Max(1, (remaining + dt - 1) / dt);
      } else if (mode == "recycle") {
        float delay = Convert.ToSingle(row["delay"]);
        float dt = (float)Convert.ToInt64(row["dt_raw"]) * (1.0f / 4294967296.0f);
        float quotient = delay / dt;
        expected["frames"] = delay <= 0.00001f ? 0 : Math.Max(1, (int)Math.Round((double)quotient, MidpointRounding.ToEven));
      } else throw new Exception("Unsupported reference case");
      result.Add(new Dictionary<string,object>{{"input",row},{"expected",expected}});
    }
    Console.Write(serializer.Serialize(new Dictionary<string,object>{
      {"reference_kind","source-owned CSharp static reconstruction; no client runtime oracle"},
      {"vectors",result}}));
  }
}
