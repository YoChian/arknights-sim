// Owned C# IEnumerator/Stack translation of static native evidence.
// No game assembly is loaded or called; this is not a live-client oracle.
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Web.Script.Serialization;

class TimelineReference {
    static readonly object FrameMarker = new object();
    class Context {
        public int Frame;
        public float Delta;
        public long DeltaRaw;
        public List<object> Events = new List<object>();
        public void Log(string kind, string label) {
            Events.Add(new Dictionary<string,object> {
                {"frame",Frame}, {"kind",kind}, {"label",label}
            });
        }
    }
    struct StackItem {
        public bool First;
        public IEnumerator Enumerator;
        public StackItem(bool first, IEnumerator e) { First=first; Enumerator=e; }
    }
    class Runner {
        Stack<StackItem> Routines = new Stack<StackItem>();
        public int Calls;
        public Runner(IEnumerator root) { Routines.Push(new StackItem(true,root)); }
        public bool Active { get { return Routines.Count!=0; } }
        public int Depth { get { return Routines.Count; } }
        public bool MoveNext() {
            ++Calls;
            int operations=0;
            while (Routines.Count!=0) {
                if (++operations>100000) throw new Exception("Diagnostic operation limit");
                StackItem old=Routines.Pop();
                if (!old.Enumerator.MoveNext()) {
                    if (old.First) break;
                    continue;
                }
                Routines.Push(new StackItem(false,old.Enumerator));
                IEnumerator nested=old.Enumerator.Current as IEnumerator;
                if (nested==null) break;
                Routines.Push(new StackItem(true,nested));
            }
            return Active;
        }
    }
    static Dictionary<string,object> D(object x) { return (Dictionary<string,object>)x; }
    static ArrayList A(object x) { return (ArrayList)x; }
    static int I(object x) { return Convert.ToInt32(x,CultureInfo.InvariantCulture); }
    static float F(object x) { return Convert.ToSingle(x,CultureInfo.InvariantCulture); }
    static float FromBits(string bits) {
        return BitConverter.ToSingle(BitConverter.GetBytes(Convert.ToUInt32(bits,16)),0);
    }
    static string Bits(float x) { return BitConverter.ToUInt32(BitConverter.GetBytes(x),0).ToString("x8"); }
    static int WaitFrames(float delay,float delta) {
        float quotient=delay/delta;
        return Math.Max(1,(int)Math.Round((double)quotient,MidpointRounding.ToEven));
    }
    static IEnumerator Wait(float delay,Context context) {
        int count=WaitFrames(delay,context.Delta);
        for (int i=0;i<count;++i) yield return FrameMarker;
    }
    static IEnumerator While(Func<bool> predicate) {
        do { yield return FrameMarker; } while (predicate());
    }
    static IEnumerator Execute(Dictionary<string,object> item,Context context) {
        context.Log(item.ContainsKey("kind")?(string)item["kind"]:"execute",(string)item["label"]);
        int frames=item.ContainsKey("frames")?I(item["frames"]):1;
        for (int i=0;i<frames;++i) yield return FrameMarker;
    }
    static IEnumerator Queue(ArrayList items,Context context) {
        float planned=0;
        foreach (object value in items) {
            var item=D(value); float time=F(item["time"]);
            if (planned<time) yield return Wait(time-planned,context);
            if (!item.ContainsKey("isValid") || (bool)item["isValid"])
                yield return Execute(item,context);
            planned=time;
        }
    }
    static IEnumerator Sequence(ArrayList operations,Context context) {
        foreach (object value in operations) {
            var operation=D(value);
            string op=(string)operation["op"];
            if (op=="event") {
                context.Log("event",(string)operation["label"]);
            } else if (op=="child") {
                yield return Sequence(A(operation["ops"]),context);
            } else if (op=="marker") {
                string valueKind=operation.ContainsKey("value")?(string)operation["value"]:"null";
                yield return valueKind=="null"?null:valueKind=="list"?(object)new ArrayList():FrameMarker;
            } else if (op=="wait") {
                yield return Wait(F(operation["delay"]),context);
            } else if (op=="while") {
                ArrayList values=A(operation["values"]); int index=0;
                string label=(string)operation["label"];
                yield return While(delegate {
                    bool result=(bool)values[Math.Min(index,values.Count-1)]; ++index;
                    context.Log("predicate",label+":"+(result?"true":"false"));
                    return result;
                });
            } else if (op=="queue") {
                yield return Queue(A(operation["items"]),context);
            } else throw new Exception("Unknown DSL operation: "+op);
        }
    }
    static IEnumerator Fragment(Dictionary<string,object> fragment,Context context) {
        ArrayList items=A(fragment["items"]);
        if (items.Count!=0) yield return Queue(items,context);
        yield return While(delegate { return false; });
    }
    static IEnumerator Wave(Dictionary<string,object> wave,Context context,int index) {
        yield return Wait(F(wave["preDelay"]),context);
        foreach (object fragment in A(wave["fragments"])) yield return Fragment(D(fragment),context);
        yield return While(delegate { return false; });
        yield return Wait(F(wave["postDelay"]),context);
        context.Log("wave_complete",index.ToString(CultureInfo.InvariantCulture));
    }
    static IEnumerator Kernel(ArrayList waves,Context context) {
        int index=0;
        foreach (object wave in waves) yield return Wave(D(wave),context,index++);
        // Fixture sets external final complete and creates no counted enemy.
        yield return While(delegate { return false; });
        context.Log("kernel_complete","");
    }
    static Dictionary<string,object> Run(Dictionary<string,object> spec,bool kernel) {
        var context=new Context { Delta=FromBits((string)spec["delta_bits"]),
                                  DeltaRaw=spec.ContainsKey("dt_raw")?long.Parse((string)spec["dt_raw"]):0 };
        var root=kernel?Kernel(A(spec["waves"]),context):Sequence(A(spec["ops"]),context);
        var runner=new Runner(root); var trace=new List<object>();
        for (int frame=0;frame<I(spec["max_frames"]);++frame) {
            context.Frame=frame;
            bool active=runner.MoveNext();
            var row=new Dictionary<string,object> {
                {"frame",frame}, {"calls",runner.Calls}, {"active",active},
                {"depth",runner.Depth}, {"event_count",context.Events.Count}
            };
            if (kernel) row["time_raw"]=unchecked(frame*context.DeltaRaw).ToString(CultureInfo.InvariantCulture);
            trace.Add(row);
            if (!active) break;
        }
        return new Dictionary<string,object> {
            {"name",spec["name"]}, {"trace",trace}, {"events",context.Events},
            {"completed",!runner.Active}, {"delta_bits",spec["delta_bits"]}
        };
    }
    static void Main(string[] args) {
        var json=new JavaScriptSerializer { MaxJsonLength=int.MaxValue };
        var input=json.Deserialize<Dictionary<string,object>>(File.ReadAllText(args[0]));
        var cases=new List<object>(); var kernels=new List<object>(); var waits=new List<object>();
        foreach (object spec in A(input["cases"])) cases.Add(Run(D(spec),false));
        foreach (object spec in A(input["kernels"])) kernels.Add(Run(D(spec),true));
        foreach (object value in A(input["waits"])) {
            var w=D(value); float delay=FromBits((string)w["delay_bits"]),delta=FromBits((string)w["delta_bits"]);
            waits.Add(new Dictionary<string,object> {
                {"delay_bits",w["delay_bits"]}, {"delta_bits",w["delta_bits"]},
                {"quotient_bits",Bits(delay/delta)}, {"frames",WaitFrames(delay,delta)}
            });
        }
        var output=new Dictionary<string,object> {
            {"oracle_scope","independent C# IEnumerator translation of static native paths; not game runtime"},
            {"runtime",Environment.Version.ToString()}, {"pointer_bits",IntPtr.Size*8},
            {"cases",cases}, {"kernels",kernels}, {"waits",waits}
        };
        File.WriteAllText(args[1],json.Serialize(output));
        Console.WriteLine("Timeline reference: {0} coroutine cases, {1} kernels, {2} waits",cases.Count,kernels.Count,waits.Count);
    }
}
