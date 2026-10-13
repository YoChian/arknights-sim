// Independent C# translation of retained native movement arithmetic.
// No game binary, game runtime, process or network API is referenced/loaded.
using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Text;
using System.Web.Script.Serialization;

public static class RuntimeMovementReference {
  static JavaScriptSerializer J=new JavaScriptSerializer{MaxJsonLength=16000000};
  static Dictionary<string,object> D(object o){return (Dictionary<string,object>)o;}
  static object[] A(object o){return (object[])o;}
  static int I(object o){return Convert.ToInt32(o);}
  static bool B(object o){return Convert.ToBoolean(o);}
  static float Read(object o){return BitConverter.ToSingle(BitConverter.GetBytes(Convert.ToUInt32(o)),0);}
  static long Bits(float x){return BitConverter.ToUInt32(BitConverter.GetBytes(x),0);}
  [MethodImpl(MethodImplOptions.NoInlining)] static float F(float x){return x;}
  struct V {
    public float x,y;
    public V(float x,float y){this.x=F(x);this.y=F(y);}
    public float Sq(){return F(F(y*y)+F(x*x));}
    public float Mag(){return F((float)Math.Sqrt((double)Sq()));}
    public V Norm(){float m=Mag();return m>1e-5f?new V(F(x/m),F(y/m)):new V(0,0);}
    public V Add(V o){return new V(F(x+o.x),F(y+o.y));}
    public V Sub(V o){return new V(F(x-o.x),F(y-o.y));}
    public V Scale(float s){return new V(F(x*s),F(y*s));}
    public bool Zero(){return Math.Abs(x)<=1e-5f&&Math.Abs(y)<=1e-5f;}
    public long[] Dump(){return new long[]{Bits(x),Bits(y)};}
  }
  static V Vector(object o){var a=A(o);return new V(Read(a[0]),Read(a[1]));}
  static V Clamp(V v,float max){if(v.Sq()<=F(max*max))return v;float m=v.Mag();return new V(F(F(v.x/m)*max),F(F(v.y/m)*max));}
  static V Deterministic(V v,bool enabled){if(!enabled)return v;return new V(F((float)(Math.Round((double)v.x*10000.0,MidpointRounding.ToEven)/10000.0)),F((float)(Math.Round((double)v.y*10000.0,MidpointRounding.ToEven)/10000.0)));}
  class Grid {
    public bool[,] pass,obstacle; public int h,w;
    public Grid(object o){var rows=A(o);h=rows.Length;w=A(rows[0]).Length;pass=new bool[h,w];obstacle=new bool[h,w];for(int r=0;r<h;r++)for(int c=0;c<w;c++){var t=A(A(rows[r])[c]);pass[r,c]=B(t[0]);obstacle[r,c]=B(t[1]);}}
    public bool Valid(int r,int c){return r>=0&&r<h&&c>=0&&c<w;}
  }
  static int[,] Neighbors=new int[,]{{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
  static V Avoid(Grid g,V offset,V foot,float half){
    int r=(int)Math.Round(offset.y),c=(int)Math.Round(offset.x);if(!g.Valid(r,c))return new V(0,0);
    V answer=new V(0,0);
    if(!g.pass[r,c]){float best=float.MaxValue;for(int i=0;i<8;i++){int dr=Neighbors[i,0],dc=Neighbors[i,1],nr=r+dr,nc=c+dc;if(!g.Valid(nr,nc)||!g.pass[nr,nc])continue;float dist=offset.Sub(new V(nc,nr)).Sq();if(dist<best){best=dist;answer=new V(dc,dr);}}return answer;}
    for(int i=0;i<8;i++){
      int dr=Neighbors[i,0],dc=Neighbors[i,1],nr=r+dr,nc=c+dc;if(!g.Valid(nr,nc)||(g.pass[nr,nc]&&!g.obstacle[nr,nc]))continue;
      float ex=F(foot.x+F(F(dc)*half)),ey=F(foot.y+F(half*0f));
      float px=Math.Max(0f,F(F(ex-F(c))*F(dc))),py=Math.Max(0f,F(F(ey-F(r))*F(dr)));
      px=F(F(Math.Abs(dc))*F(px-.25f));py=F(F(Math.Abs(dr))*F(py-.25f));
      if(px>0f&&py>0f){px=py=F(F(px+py)*.5f);}else if(Math.Abs(dr)+Math.Abs(dc)!=1||(px<=0f&&py<=0f))continue;
      float x=F(F(-px)*F(dc)),y=F(F(-py)*F(dr));answer=new V(F(F(x+x)+answer.x),F(F(y+y)+answer.y));
    }return answer.Norm();
  }
  class Controller {
    Grid grid;bool modern;float factor,max,half;V foot;public V velocity=new V(0,0),last=new V(0,0);public int ticker=0;
    public Controller(Grid g,Dictionary<string,object> t){grid=g;modern=B(t["new_steering"]);factor=Read(t["initial_steering"]);max=Read(t["max_force"]);half=Read(t["half_body_width"]);foot=Vector(t["foot_offset"]);}
    public object Tick(Dictionary<string,object> t){
      float speed=Read(t["speed"]),dt=Read(t["delta"]);V dir=Vector(t["direction"]),position=Vector(t["position"]),offset=Vector(t["offset_position"]),delta=new V(0,0);bool still=true;
      if(speed>1e-5f&&B(t["can_move"])){
        dir=dir.Norm();if(ticker>0)ticker--;if(ticker==0){V avoid=Avoid(grid,offset,position.Add(foot),half);float dot=F(F(avoid.y*dir.y)+F(avoid.x*dir.x));last=avoid.Sub(dir.Scale(dot));ticker=3;}
        float ratio=F(velocity.Mag()/speed);V correction=last.Scale(Math.Max(.5f,ratio));still=dir.Zero()&&correction.Zero();
        V force=Clamp(dir.Scale(speed).Sub(velocity).Scale(modern?factor:100f).Add(correction),modern?max:100f);
        velocity=Clamp(velocity.Add(force.Scale(dt)),speed);delta=velocity.Scale(dt);
      }
      return new{delta=delta.Dump(),velocity=velocity.Dump(),last_avoid=last.Dump(),ticker=ticker,still=still};
    }
  }
  public static int Main(string[] args){
    var input=D(J.DeserializeObject(File.ReadAllText(args[0])));var rounding=new List<object>();var avoids=new List<object>();var controllers=new List<object>();
    foreach(object o in A(input["rounding"])){var t=D(o);rounding.Add(Deterministic(Vector(t["position"]),B(t["enabled"])).Dump());}
    foreach(object o in A(input["avoidance"])){var t=D(o);avoids.Add(Avoid(new Grid(t["grid"]),Vector(t["offset_position"]),Vector(t["foot_position"]),Read(t["half_body_width"])).Dump());}
    foreach(object o in A(input["controllers"])){var t=D(o);var ctr=new Controller(new Grid(t["grid"]),D(t["context"]));var frames=new List<object>();foreach(object step in A(t["steps"]))frames.Add(ctr.Tick(D(step)));controllers.Add(frames);}
    File.WriteAllText(args[1],J.Serialize(new{scope="independent translated C# arithmetic/controller; not native/client oracle",rounding=rounding,avoidance=avoids,controllers=controllers}),new UTF8Encoding(false));return 0;
  }
}
