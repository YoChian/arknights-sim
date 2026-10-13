// Self-authored, bounded implementation cross-check. Not target/client code.
using System;
using System.IO;
using System.Numerics;
using System.Collections.Generic;

class SkillCycleReference {
    const long ONE = 4294967296L;
    const long EPS = 42950L;
    static long Divide(long a, long b) {
        if (b == 0) throw new Exception("outside bounded reference");
        BigInteger n = BigInteger.Abs(new BigInteger(a)) << 32;
        BigInteger d = BigInteger.Abs(new BigInteger(b));
        // Independent rational form, for the bounded no-overflow input scope.
        long raw = (long)((2 * n + d) / (2 * d));
        return (a < 0) != (b < 0) ? -raw : raw;
    }
    static int RoundFP(long raw) {
        long high = raw >> 32;
        uint low = (uint)raw;
        if (low > 0x80000000U || (low == 0x80000000U && (high & 1) != 0)) high++;
        return checked((int)high);
    }
    static int Wait(long delay, long divisor) {
        return Math.Max(1, RoundFP(Divide(delay, divisor)));
    }
    static void Emit(string name, int frame, string kind, long value) {
        Console.WriteLine(name + "\t" + frame + "\t" + kind + "\t" + value);
    }
    static void Run(string line) {
        string[] p = line.Split('\t'); string name = p[0];
        int frames = int.Parse(p[1]); long dt = long.Parse(p[2]);
        long delay = long.Parse(p[3]), duration = long.Parse(p[4]), cd = long.Parse(p[5]);
        long halfFrame = long.Parse(p[6]);
        long sp = 0, spRemaining = ONE, remaining = 0, time = 0, startTime = 0;
        bool casting = false, registered = false; int state = 0, wait = 0;
        for (int frame = 1; frame <= frames; frame++) {
            time += dt;
            if (!registered && sp < 7 * ONE) {
                spRemaining -= dt;
                if (spRemaining < EPS) {
                    long count = Math.Max(0, Divide(-spRemaining, ONE) >> 32) + 1;
                    spRemaining += count * ONE;
                    sp = Math.Min(7 * ONE, sp + count * ONE);
                    Emit(name, frame, "sp", sp);
                }
            }
            remaining = Math.Max(0, remaining - dt);
            if (registered != casting) {
                registered = casting;
                Emit(name, frame, "modifier", registered ? 1 : 0);
            }
            if (!casting && Math.Abs(remaining) < EPS && sp > 7 * ONE - EPS) {
                casting = true; remaining = cd; startTime = time;
                Emit(name, frame, "start", sp);
                // Start immediately primes and yields its first fixed wait.
                state = 1; wait = Wait(delay, dt);
                sp = Math.Max(0, sp - 7 * ONE);
                registered = true;
                Emit(name, frame, "modifier", 1);
            }
            // Separate shared-simulator phase includes the just-started handle.
            if (state == 1) {
                if (--wait == 0) {
                    Emit(name, frame, "spell", 0);
                    long post = Math.Max(0, duration - (time - startTime));
                    wait = Wait(post, dt); state = 2;
                }
            } else if (state == 2 && --wait == 0) {
                casting = false; state = 0;
                if (Math.Abs(duration - cd) < EPS && remaining < halfFrame - EPS) remaining = 0;
                Emit(name, frame, "finish", 0);
            }
        }
    }
    static int Main(string[] args) {
        foreach (string line in File.ReadAllLines(args[0])) if (line.Length > 0) Run(line);
        return 0;
    }
}
