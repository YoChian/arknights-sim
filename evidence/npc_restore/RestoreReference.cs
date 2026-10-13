// Self-authored implementation reference, not extracted client code/oracle.
using System;
using System.IO;
using System.Collections.Generic;
using System.Globalization;
class RestoreReference {
    sealed class Entry { public IEnumerator<object> Iterator; public bool First;
        public Entry(IEnumerator<object> it) { Iterator=it; First=true; } }
    sealed class Runner {
        public List<Entry> Stack=new List<Entry>();
        public Runner(IEnumerator<object> root) { Stack.Add(new Entry(root)); }
        public void Tick() {
            while(Stack.Count>0) {
                Entry top=Stack[Stack.Count-1]; Stack.RemoveAt(Stack.Count-1);
                if(!top.Iterator.MoveNext()) { if(top.First) break; continue; }
                top.First=false; Stack.Add(top);
                IEnumerator<object> child=top.Iterator.Current as IEnumerator<object>;
                if(child!=null) { Stack.Add(new Entry(child)); continue; }
                break;
            }
        }
        public void Stop() { Stack.Clear(); }
    }
    sealed class Model {
        public bool Disappeared=true, Active=true; public int State=11, Hidden=-1, Transition=-1, FirstMove=-1, Frame=0;
        public Runner Coroutine;
        public Model(float dt) { Coroutine=new Runner(Hide(dt).GetEnumerator()); Coroutine.Tick(); }
        static IEnumerable<object> Wait(float dt) {
            float quotient=(float)(0.3f/dt);
            int count=Math.Max(1,(int)Math.Round((double)quotient,MidpointRounding.ToEven));
            for(int i=0;i<count;i++) yield return null;
        }
        IEnumerable<object> Hide(float dt) {
            yield return Wait(dt).GetEnumerator();
            Active=false; Hidden=Frame;
        }
        public void Tick() {
            Frame++;
            if(State==11) {
                if(!Disappeared) { Coroutine.Stop(); Active=true; State=1; Transition=Frame; }
            } else if(FirstMove<0) FirstMove=Frame;
            Coroutine.Tick();
        }
    }
    static string Bits(float f) { return BitConverter.ToUInt32(BitConverter.GetBytes(f),0).ToString("x8"); }
    public static void Main(string[] args) {
        var rows=new List<string>();
        foreach(string line in File.ReadAllLines(args[0])) {
            string[] s=line.Split(','); float dt=float.Parse(s[0],CultureInfo.InvariantCulture); int clear=int.Parse(s[1]);
            Model m=new Model(dt);
            if(clear==0) m.Disappeared=false;
            for(int f=1;f<=24;f++) { if(f==clear) m.Disappeared=false; m.Tick(); }
            // Setter arithmetic independently exercises Single precision.
            float p=float.Parse(s[2],CultureInfo.InvariantCulture);
            float r=(float)(0.123456789f*p), g=(float)(0.9f*p), b=(float)(-0.4f*p), a=(float)(0.7f*p);
            rows.Add(m.Hidden+","+m.Transition+","+m.FirstMove+","+(m.Active?1:0)+","+Bits(r)+","+Bits(g)+","+Bits(b)+","+Bits(a));
        }
        File.WriteAllLines(args[1],rows.ToArray());
    }
}
