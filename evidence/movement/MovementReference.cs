// Independent translation of the retained native arithmetic/path evidence.
// Does not reference, load, execute or communicate with any game artifact.
using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using System.Text;
using System.Web.Script.Serialization;

public static class MovementReference {
  static JavaScriptSerializer J = new JavaScriptSerializer { MaxJsonLength = 16000000 };
  static Dictionary<string,object> D(object o) { return (Dictionary<string,object>)o; }
  static object[] A(object o) { return (object[])o; }
  static int I(object o) { return Convert.ToInt32(o); }
  static bool B(object o) { return Convert.ToBoolean(o); }
  static float From(object o) { return BitConverter.ToSingle(BitConverter.GetBytes(Convert.ToUInt32(o)),0); }
  static long Bits(float x) { return BitConverter.ToUInt32(BitConverter.GetBytes(x),0); }
  [MethodImpl(MethodImplOptions.NoInlining)] static float F(float x) { return x; }
  struct V {
    public float x,y;
    public V(float x,float y) { this.x=F(x);this.y=F(y); }
    public float Sq() { return F(F(y*y)+F(x*x)); }
    public float Mag() { return F((float)Math.Sqrt((double)Sq())); }
    public V Norm() { float m=Mag();return m > 1e-5f ? new V(F(x/m),F(y/m)) : new V(0,0); }
    public V Sub(V o) { return new V(F(x-o.x),F(y-o.y)); }
    public long[] ToBits() { return new long[]{Bits(x),Bits(y)}; }
  }
  static V Clamp(V v,float max) {
    if(v.Sq()<=F(max*max)) return v;
    float m=v.Mag();return new V(F(F(v.x/m)*max),F(F(v.y/m)*max));
  }
  class Tile {
    public int mask,gotoMask; public bool highCost,obstacle;
    public Tile(object o) { var t=D(o);mask=I(t["passable_mask"]);gotoMask=I(t["walk_goto_mask"]);highCost=B(t["override_obstacle_move_cost"]);obstacle=B(t["is_obstacle_like"]); }
    public bool Pass() { return (mask&1)>0; }
    public bool Goto(int d) { return Pass() && (gotoMask & (1<<d))>0; }
  }
  class N {
    public int r,c,nr,nc,dist=-1,dtf=-1; public bool has,open;public Tile tile;public V turn=new V(0,0);
    public N(int r,int c,Tile t) { this.r=r;this.c=c;nr=r;nc=c;tile=t; }
    public bool Bad() { return dist<0 || tile.obstacle; }
    public V Dir() { return dist>=0 && has ? new V(nc-c,nr-r).Norm() : new V(0,0); }
    public object Dump() { return new { grid=new int[]{r,c}, next=new int[]{nr,nc}, distance=dist, distance_to_final=dtf, has_next=has, next_turn=turn.ToBits() }; }
  }
  static int[,] Directions = new int[,]{{1,0},{0,1},{-1,0},{0,-1}};
  static int[] Opposite = new int[]{2,3,0,1};
  static bool Ray(N[,] nodes,int sr,int sc,int er,int ec) {
    int dr=Math.Abs(er-sr),dc=Math.Abs(ec-sc);bool steep=dc<dr;
    int first=steep?sr:sc,last=steep?er:ec,v0=steep?sc:sr,v1=steep?ec:er;
    if(last<first) { int q=first;first=last;last=q;q=v0;v0=v1;v1=q; }
    int dx=last-first,dy=Math.Abs(v1-v0),sy=v0<v1?1:-1;
    Func<int,int,N> at=(u,v)=>steep?nodes[u,v]:nodes[v,u];
    if(dy<2) for(int r=Math.Min(sr,er);r<=Math.Max(sr,er);r++) for(int c=Math.Min(sc,ec);c<=Math.Max(sc,ec);c++) if(nodes[r,c].Bad())return false;
    int error=-dx,minor=v0,forward=steep?0:1,side=steep?(sy>0?1:3):(sy>0?0:2);
    for(int u=first;u<=last;u++) {
      N n=at(u,minor);
      if(n.Bad()||!n.tile.Goto(forward))return false;
      error+=2*dy;
      if(u<last && error>=0) {
        N sid=at(u,minor+sy),front=at(u+1,minor);
        if(sid.Bad()||front.Bad()||!n.tile.Goto(side)||!front.tile.Goto(side)||!sid.tile.Goto(forward))return false;
        minor+=sy;error-=2*dx;
      }
    }
    return true;
  }
  static N[,] Compute(Tile[,] tiles,int tr,int tc,bool smooth) {
    int h=tiles.GetLength(0),w=tiles.GetLength(1);var nodes=new N[h,w];
    for(int r=0;r<h;r++)for(int c=0;c<w;c++)nodes[r,c]=new N(r,c,tiles[r,c]);
    var queue=new Queue<N>();N target=nodes[tr,tc];
    if(target.tile.Pass()) { target.dist=0;target.open=true;queue.Enqueue(target); }
    while(queue.Count>0) {
      N cur=queue.Dequeue();cur.open=false;
      for(int d=0;d<4;d++) {
        int r=cur.r+Directions[d,0],c=cur.c+Directions[d,1];
        if(r<0||c<0||r>=h||c>=w)continue;N n=nodes[r,c];
        if(!n.tile.Goto(Opposite[d]))continue;
        int distance=cur.dist+(n.tile.highCost?1000:1);
        if(n.dist<0 || distance<n.dist) {
          n.nr=cur.r;n.nc=cur.c;n.dist=distance;n.has=true;
          if(!n.open) { n.open=true;queue.Enqueue(n); }
        }
      }
    }
    for(int r=0;r<h;r++)for(int c=0;c<w;c++) {
      N n=nodes[r,c];n.dtf=n.dist;
      if(smooth && n.dist>=0 && n.has) {
        int nr=n.nr,nc=n.nc;
        while(nodes[nr,nc].has) {
          N successor=nodes[nr,nc];
          if(!Ray(nodes,r,c,successor.nr,successor.nc))break;
          nr=successor.nr;nc=successor.nc;
        }
        n.nr=nr;n.nc=nc;
      }
    }
    return nodes;
  }
  static V Turn(N[,] nodes,N node) {
    if(node.open)return node.turn;node.open=true;
    if(!node.has) { node.turn=new V(0,0);return node.turn; }
    N successor=nodes[node.nr,node.nc];V next=successor.Dir();
    node.turn=next.Sub(node.Dir()).Sq() >= F(1e-5f*1e-5f) ? next : Turn(nodes,successor);
    return node.turn;
  }
  static object[] Dump(N[,] nodes) {
    var result=new List<object>();for(int r=0;r<nodes.GetLength(0);r++)for(int c=0;c<nodes.GetLength(1);c++)result.Add(nodes[r,c].Dump());return result.ToArray();
  }
  public static void Main(string[] args) {
    var input=D(J.DeserializeObject(File.ReadAllText(args[0])));var geom=new List<object>();var paths=new List<object>();
    foreach(object o in A(input["geometry"])) {
      var item=D(o);V v=new V(From(item["x"]),From(item["y"])),target=new V(From(item["target_x"]),From(item["target_y"]));
      float radius=From(item["radius"]);bool zero=Math.Abs(v.x)<=1e-5f && Math.Abs(v.y)<=1e-5f;
      geom.Add(new { name=item["name"], squared=Bits(v.Sq()),magnitude=Bits(v.Mag()),normalized=v.Norm().ToBits(),clamped=Clamp(v,From(item["max"])).ToBits(),
        grid=new int[]{(int)Math.Round((double)v.y,MidpointRounding.ToEven),(int)Math.Round((double)v.x,MidpointRounding.ToEven)},is_zero=zero,
        safe_normalized=(zero?new V(0,0):v.Norm()).ToBits(),check_distance=F(radius*radius)>=v.Sub(target).Sq() });
    }
    foreach(object o in A(input["paths"])) {
      var item=D(o);object[] rows=A(item["rows"]);int h=rows.Length,w=A(rows[0]).Length;Tile[,] tiles=new Tile[h,w];
      for(int r=0;r<h;r++)for(int c=0;c<w;c++)tiles[r,c]=new Tile(A(rows[r])[c]);object[] target=A(item["target"]);int tr=I(target[0]),tc=I(target[1]);
      N[,] raw=Compute(tiles,tr,tc,false),smooth=Compute(tiles,tr,tc,true);var rays=new List<object>();
      foreach(object q in A(item["rays"])) { var ray=D(q);object[] start=A(ray["start"]),end=A(ray["end"]);rays.Add(new { clear=Ray(raw,I(start[0]),I(start[1]),I(end[0]),I(end[1])) }); }
      for(int r=0;r<h;r++)for(int c=0;c<w;c++)smooth[r,c].open=false;
      smooth[tr,tc].open=true;smooth[tr,tc].turn=new V(0,0);for(int r=0;r<h;r++)for(int c=0;c<w;c++)Turn(smooth,smooth[r,c]);
      paths.Add(new { name=item["name"],raw=Dump(raw),smooth=Dump(smooth),rays=rays });
    }
    File.WriteAllText(args[1],J.Serialize(new { scope="independent reconstructed C#; no game/runtime oracle", runtime=Environment.Version.ToString(), geometry=geom,paths=paths }),new UTF8Encoding(false));
    Console.WriteLine("geometry="+geom.Count+" paths="+paths.Count);
  }
}
