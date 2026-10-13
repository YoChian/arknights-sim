using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Web.Script.Serialization;
using System.IO;

// Independent CLR primitives and straightforward ordered-list reference.
// No game assembly or extracted executable code is loaded.
public class NativeNpcActionsReference {
  static string Text(object x) { return x==null ? null : Convert.ToString(x,CultureInfo.InvariantCulture); }
  static long Long(object x) { return Convert.ToInt64(x,CultureInfo.InvariantCulture); }
  static bool Bool(object x) { return Convert.ToBoolean(x,CultureInfo.InvariantCulture); }
  static void Assign(List<Dictionary<string,object>> rows,string key,float number,string text) {
    string lower=key.ToLower();
    var next=new Dictionary<string,object>{{"key",lower},{"value",(double)number},
      {"value_bits",BitConverter.ToUInt32(BitConverter.GetBytes(number),0)},{"text",text}};
    for(int i=0;i<rows.Count;i++) {
      if(String.Compare((string)rows[i]["key"],key,true)==0) {rows[i]=next;return;}
    }
    rows.Add(next);
  }
  public static void Main(string[] args) {
    try { Run(args); }
    catch(Exception e) {Console.WriteLine("REFERENCE_ERROR:"+e.GetType().FullName);Environment.ExitCode=1;}
  }
  public static void Run(string[] args) {
    System.Threading.Thread.CurrentThread.CurrentCulture=CultureInfo.InvariantCulture;
    var json=new JavaScriptSerializer();json.MaxJsonLength=2000000;
    var input=json.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
    var results=new List<object>();
    foreach(Dictionary<string,object> c in (ArrayList)input["cases"]) {
      string kind=(string)c["kind"];
      var expected=new Dictionary<string,object>();
      if(kind=="floor") {
        float value=Convert.ToSingle(c["value"],CultureInfo.InvariantCulture);
        expected["value"]=(int)Math.Floor((double)value);
      } else if(kind=="ge") {
        long threshold=unchecked(Long(c["right"])-42950L);
        expected["value"]=Long(c["left"])>=threshold;
      } else if(kind=="condition") {
        int condition=Convert.ToInt32(c["condition"]);bool previous=Bool(c["previous"]);
        expected["value"]=condition==0 || condition==1&&previous || condition==2&&!previous;
      } else if(kind=="uid") {
        expected["value"]=!Bool(c["null"])&&Bool(c["exists"])&&Long(c["current"])==Long(c["saved"]);
      } else if(kind=="bind") {
        string prefix=(string)c["prefix"]+".";
        var rows=new List<Dictionary<string,object>>();
        var source=(ArrayList)c["rows"];
        foreach(Dictionary<string,object> row in source) {
          string key=(string)row["key"];
          if(key.StartsWith(prefix,StringComparison.OrdinalIgnoreCase))
            Assign(rows,key.Substring(prefix.Length),Convert.ToSingle(row["value"],CultureInfo.InvariantCulture),null);
        }
        foreach(Dictionary<string,object> row in source) {
          string key=(string)row["key"],text=row.ContainsKey("text")?Text(row["text"]):null;
          if(key.StartsWith(prefix,StringComparison.OrdinalIgnoreCase)&&!String.IsNullOrEmpty(text))
            Assign(rows,key.Substring(prefix.Length),0,text);
        }
        expected["rows"]=rows;
      } else {throw new InvalidOperationException("Unknown reference kind");}
      results.Add(expected);
    }
    Console.WriteLine(json.Serialize(new Dictionary<string,object>{{"reference_kind","independent CLR primitives and ordered List<DataPair> reference"},{"game_code_loaded",false},{"results",results}}));
  }
}
