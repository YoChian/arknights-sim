// Independent bounded translation check. This does not execute client code.
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Numerics;

public static class DeviceReference
{
    const long One = 4294967296L;
    const long Eps = 42950L;
    static long Divide(long a, long b)
    {
        if (b == 0) return -One;
        BigInteger n = BigInteger.Abs(new BigInteger(a)) * One;
        BigInteger d = BigInteger.Abs(new BigInteger(b));
        BigInteger r;
        BigInteger q = BigInteger.DivRem(n, d, out r);
        if (r * 2 >= d) q++;
        if ((a < 0) != (b < 0)) q = -q;
        return (long)q; // Bounded fixtures only; no saturation sentinels.
    }
    static int Tick(ref long remaining, long period, long delta)
    {
        remaining -= delta;
        if (remaining >= Eps) return 0;
        long count = Math.Max(0L, Divide(-remaining, period) >> 32) + 1;
        remaining += period * count;
        return (int)count;
    }
    public static void Main()
    {
        string line;
        while ((line = Console.ReadLine()) != null)
        {
            string[] p = line.Split('|');
            if (p[0] == "T")
            {
                long period = long.Parse(p[1]);
                long remaining = long.Parse(p[2]);
                long delta = long.Parse(p[3]);
                int count = Tick(ref remaining, period, delta);
                Console.WriteLine(count + "|" + remaining);
            }
            else if (p[0] == "W")
            {
                float delay = float.Parse(p[1], CultureInfo.InvariantCulture);
                float dt = float.Parse(p[2], CultureInfo.InvariantCulture);
                float quotient = delay / dt;
                int frames = Math.Max(1, (int)Math.Round((double)quotient, MidpointRounding.ToEven));
                // Deterministic StartCoroutine primes one wait marker immediately.
                int remainingMarkers = frames - 1;
                int laterTick = 0;
                while (remainingMarkers >= 0) { laterTick++; remainingMarkers--; }
                Console.WriteLine(frames + "|" + laterTick);
            }
            else if (p[0] == "B")
            {
                long life = long.Parse(p[1]);
                bool started = p[2] == "1", marked = p[3] == "1";
                Console.WriteLine((marked || (started && Math.Abs(life) < Eps)) ? "1" : "0");
            }
            else if (p[0] == "S")
            {
                long remaining = One;
                var frames = new List<int>();
                for (int frame = 1; frame <= int.Parse(p[1]); frame++)
                    if (Tick(ref remaining, One, 143165440L) > 0) frames.Add(frame);
                Console.WriteLine(string.Join(",", frames));
            }
            else throw new Exception("unsupported reference fixture");
        }
    }
}
