// Independent C# translation of static Torappu.FP native instructions.
// Does not load or call any game artifact. Not a running-client oracle.
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Numerics;
using System.Web.Script.Serialization;

class FPReference {
    const long One = 1L << 32;
    const long MaxValue = long.MaxValue - 1;
    const long MinValue = long.MinValue + 2;
    static long Wrap(BigInteger x) {
        BigInteger modulus = BigInteger.One << 64;
        x = (x % modulus + modulus) % modulus;
        if (x >= (BigInteger.One << 63)) x -= modulus;
        return (long)x;
    }
    static long Mul(long x, long y) {
        unchecked {
            ulong xl = (uint)x, yl = (uint)y;
            long xh = x >> 32, yh = y >> 32;
            long value = yh * xh * One + (long)(xl * yl >> 32)
                       + (long)yl * xh + (long)xl * yh;
            if (value != Wrap(((BigInteger)x * y) >> 32))
                throw new Exception("Native limb/wide multiply identity failed");
            return value;
        }
    }
    static int LeadingZeroes(ulong x) {
        int n = 0;
        while ((x & 0xF000000000000000UL) == 0) { n += 4; x <<= 4; }
        while ((long)x >= 0) { ++n; x <<= 1; }
        return n;
    }
    static long Div(long x, long y) {
        if (y == 0) return -One;
        unchecked {
            ulong remainder = (ulong)(x < 0 ? -x : x);
            ulong divider = (ulong)(y < 0 ? -y : y);
            ulong quotient = 0;
            int bitPosition = 33;
            while ((divider & 0xF) == 0 && bitPosition > 3) {
                divider >>= 4; bitPosition -= 4;
            }
            while (remainder != 0 && bitPosition >= 0) {
                int shift = Math.Min(LeadingZeroes(remainder), bitPosition);
                remainder <<= shift;
                bitPosition -= shift;
                ulong part = remainder / divider;
                quotient += part << bitPosition;
                if ((part & ~(ulong.MaxValue >> bitPosition)) != 0)
                    return (x ^ y) < 0 ? MinValue : MaxValue;
                remainder = (remainder % divider) << 1;
                --bitPosition;
            }
            long result = (long)((quotient + 1) >> 1);
            return (x ^ y) < 0 ? -result : result;
        }
    }
    static long Round(long x) {
        unchecked {
            uint low = (uint)x;
            long floor = (x >> 32) << 32;
            return low > 0x80000000U || (low == 0x80000000U && (floor & One) != 0)
                ? floor + One : floor;
        }
    }
    static long Sat(BigInteger x) {
        if (x > long.MaxValue) return long.MaxValue;
        if (x < long.MinValue) return long.MinValue;
        return (long)x;
    }
    static string S(long x) { return x.ToString(CultureInfo.InvariantCulture); }
    static long L(object x) { return long.Parse((string)x, CultureInfo.InvariantCulture); }
    static string FBits(float f) { return BitConverter.ToUInt32(BitConverter.GetBytes(f), 0).ToString("x8"); }
    static string DBits(double d) { return BitConverter.ToUInt64(BitConverter.GetBytes(d), 0).ToString("x16"); }
    static void Main(string[] args) {
        var serializer = new JavaScriptSerializer { MaxJsonLength = int.MaxValue };
        var input = serializer.Deserialize<Dictionary<string, object>>(File.ReadAllText(args[0]));
        var pairs = new List<object>();
        foreach (object item in (ArrayList)input["pairs"]) {
            var p = (ArrayList)item; long x = L(p[0]), y = L(p[1]);
            var r = new Dictionary<string, object>();
            r["x"] = S(x); r["y"] = S(y);
            r["add"] = S(unchecked(x+y)); r["sub"] = S(unchecked(x-y));
            r["mul"] = S(Mul(x,y)); r["div"] = S(Div(x,y));
            r["mod"] = y == 0 ? null : S(x == long.MinValue && y == -1 ? 0 : x%y);
            r["cmp"] = x.CompareTo(y);
            r["overflow_add"] = S(Sat((BigInteger)x+y));
            r["overflow_sub"] = S(Sat((BigInteger)x-y));
            pairs.Add(r);
        }
        var unary = new List<object>();
        foreach (object item in (ArrayList)input["raw_values"]) {
            long x = L(item);
            var r = new Dictionary<string, object>();
            r["raw"] = S(x); r["neg"] = S(x==long.MinValue ? MaxValue : -x);
            r["abs"] = S(x==long.MinValue ? MaxValue : Math.Abs(x));
            r["floor"] = S((x>>32)<<32);
            r["ceiling"] = S(unchecked(((x>>32)<<32) + ((uint)x==0 ? 0 : One)));
            r["round"] = S(Round(x)); r["int"] = x>>32;
            r["float_bits"] = FBits((float)x * (float)Math.Pow(2,-32));
            r["double_bits"] = DBits((double)x * Math.Pow(2,-32));
            unary.Add(r);
        }
        var f32 = new List<object>();
        foreach (object item in (ArrayList)input["float32_bits"]) {
            uint bits = Convert.ToUInt32((string)item,16);
            float x = BitConverter.ToSingle(BitConverter.GetBytes(bits),0);
            float scaled = x * 4294967296.0f;
            long raw = unchecked((long)scaled);
            f32.Add(new Dictionary<string,object> {{"bits",item}, {"raw",S(raw)}, {"scaled_bits",FBits(scaled)}});
        }
        var f64 = new List<object>();
        foreach (object item in (ArrayList)input["double_bits"]) {
            ulong bits = Convert.ToUInt64((string)item,16);
            double x = BitConverter.ToDouble(BitConverter.GetBytes(bits),0);
            double scaled = x * 4294967296.0;
            long raw = unchecked((long)scaled);
            f64.Add(new Dictionary<string,object> {{"bits",item}, {"raw",S(raw)}, {"scaled_bits",DBits(scaled)}});
        }
        var output = new Dictionary<string,object> {
            {"oracle_scope","independent C# translation of native instructions; not game runtime"},
            {"reference_runtime",Environment.Version.ToString()},
            {"reference_pointer_bits",IntPtr.Size*8},
            {"pairs",pairs}, {"unary",unary}, {"float32",f32}, {"double",f64}
        };
        File.WriteAllText(args[1],serializer.Serialize(output));
        Console.WriteLine("FP reference wrote {0} pairs, {1} unary, {2} float32, {3} double",pairs.Count,unary.Count,f32.Count,f64.Count);
    }
}
