// Independent CLR model of the PE-bound iterator algorithm, not a game oracle.
// No client assemblies or Unity objects are loaded.
using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Web.Script.Serialization;

public class NativeBuffContainerReference {
  class Value { public int Uid, Priority; }
  class Ptr {
    public Value Value; public int Captured;
    public Value Resolve() { return Value != null && Value.Uid == Captured ? Value : null; }
  }
  class Iterator {
    public List<Ptr> Buffer; public int Index; public bool Reverse, Disposed;
    public Queue Owner;
    public void Reset(List<Ptr> buffer) { Buffer=buffer; Index=Reverse ? buffer.Count : -1; Disposed=false; }
    public bool Next() { Index += Reverse ? -1 : 1; return Reverse ? Index>=0 : Index<Buffer.Count; }
    public Ptr Current { get { return Buffer[Index]; } }
    public void Dispose() {
      if (Disposed) return;
      Disposed=true; Owner.Depth--;
      (Reverse ? Owner.BackPool : Owner.ForwardPool).Push(this);
    }
  }
  class Queue {
    public List<Ptr> Live=new List<Ptr>(), Snapshot=new List<Ptr>();
    public Stack<Iterator> ForwardPool=new Stack<Iterator>(), BackPool=new Stack<Iterator>();
    public int Depth;
    public void Add(Ptr p) {
      if (p.Resolve()==null) { Live.Add(p); return; }
      int i=Live.Count-1;
      for (;i>=0;i--) {
        Value old=Live[i].Resolve();
        if (old!=null && old.Priority>=p.Resolve().Priority) break;
      }
      Live.Insert(i+1,p);
    }
    public void Remove(Value value) {
      for (int i=Live.Count-1;i>=0;i--) {
        Value old=Live[i].Resolve();
        if (old!=null && old.Uid==value.Uid) { Live.RemoveAt(i); return; }
      }
    }
    public Iterator Begin(bool reverse) {
      if (Depth==0) { Snapshot.Clear(); Snapshot.AddRange(Live); }
      Depth++;
      Stack<Iterator> pool=reverse ? BackPool : ForwardPool;
      Iterator it=pool.Count==0 ? new Iterator { Owner=this, Reverse=reverse } : pool.Pop();
      it.Reset(Snapshot); return it;
    }
  }
  public static void Main(string[] args) {
    var serializer=new JavaScriptSerializer { MaxJsonLength=10000000 };
    var document=serializer.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
    foreach(Dictionary<string,object> vector in (ArrayList)document["vectors"]) {
      var q=new Queue(); var values=new Dictionary<int,Value>();
      var stack=new Stack<Iterator>(); var output=new List<int>();
      foreach(ArrayList op in (ArrayList)vector["operations"]) {
        string action=(string)op[0];
        if(action=="add") {
          int uid=Convert.ToInt32(op[1]);
          var value=new Value { Uid=uid, Priority=Convert.ToInt32(op[2]) };
          values.Add(uid,value); q.Add(new Ptr { Value=value, Captured=uid });
        } else if(action=="begin") stack.Push(q.Begin(Convert.ToInt32(op[1])!=0));
        else if(action=="next") { Iterator it=stack.Peek(); output.Add(it.Next() ? it.Current.Captured : -1); }
        else if(action=="end") stack.Pop().Dispose();
        else if(action=="remove") q.Remove(values[Convert.ToInt32(op[1])]);
        else if(action=="clear") q.Live.Clear();
        else if(action=="invalidate") values[Convert.ToInt32(op[1])].Uid+=10000;
        else if(action=="scan") {
          Iterator it=q.Begin(Convert.ToInt32(op[1])!=0);
          while(it.Next()) { Value value=it.Current.Resolve(); output.Add(value==null ? -3 : value.Uid); }
          it.Dispose(); output.Add(-2);
        } else if(action=="live") { foreach(Ptr p in q.Live)output.Add(p.Captured); output.Add(-2); }
      }
      if(stack.Count!=0 || q.Depth!=0)throw new Exception("Unbalanced iterator fixture");
      vector["expected"]=output;
    }
    document["oracle"]="Independent source-owned C# reference, not live client execution";
    File.WriteAllText(args[1],serializer.Serialize(document));
  }
}
