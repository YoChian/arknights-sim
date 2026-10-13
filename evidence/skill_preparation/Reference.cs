// Self-authored bounded native-semantics translation. Not a client oracle.
using System;
using System.Globalization;
using System.IO;
class Reference {
  static float FloatBits(string value) {
    uint bits=UInt32.Parse(value,NumberStyles.HexNumber,CultureInfo.InvariantCulture);
    return BitConverter.ToSingle(BitConverter.GetBytes(bits),0);
  }
  static long Raw(float value) { return unchecked((long)(float)(value*4294967296.0f)); }
  static int Main(string[] args) {
    foreach(string line in File.ReadAllLines(args[0])) {
      string[] p=line.Split('\t');
      float pre=FloatBits(p[1]),cool=FloatBits(p[2]);
      long cooldown=Raw(cool),duration=cooldown;
      // Failed animation lookup skips maxAnimScale, uses initial scale1.
      long preRaw=Raw((float)(1.0f*pre));
      Console.WriteLine(p[0]+"\t"+Math.Min(duration,preRaw)+"\t"+duration+"\t"+cooldown);
    }
    return 0;
  }
}
