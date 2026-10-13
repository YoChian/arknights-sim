// Independently compiled reference transcribed from selected local native entries.
// This program does not load or execute the game. It is not a real-client oracle.
// ctor: 0x186505240; Sample: 0x1860e0e90; Next(): 0x1860e0e40;
// Next(max): 0x186505190. Arithmetic follows x64 32-bit unchecked operations.
using System;
using System.Globalization;
using System.Text;

sealed class LegacyReference {
    const int Big = Int32.MaxValue;
    readonly int[] values = new int[56];
    int next = 0, nextp = 31;
    public LegacyReference(int seed) {
        unchecked {
            int absolute = -seed;
            if (absolute < 0) absolute = seed;
            int mj = 161803398 - absolute;
            values[55] = mj;
            int mk = 1;
            for (int i = 1; i < 55; i++) {
                int ii = (21 * i) % 55;
                values[ii] = mk;
                mk = mj - mk;
                if (mk < 0) mk += Big;
                mj = values[ii];
            }
            for (int k = 0; k < 4; k++) {
                for (int i = 1; i < 56; i++) {
                    values[i] -= values[1 + (i + 30) % 55];
                    if (values[i] < 0) values[i] += Big;
                }
            }
        }
    }
    public double Sample() {
        unchecked {
            if (++next > 55) next = 1;
            if (++nextp > 55) nextp = 1;
            int sample = values[next] - values[nextp];
            if (sample < 0) sample += Big;
            values[next] = sample;
            return sample * (1.0 / Big);
        }
    }
    public int Next() { return (int)(Sample() * Big); }
    public int Next(int max) {
        if (max < 0) throw new ArgumentOutOfRangeException("max");
        return (int)(Sample() * max);
    }
    public int NextRange(int min, int max) {
        if (max < min) throw new ArgumentOutOfRangeException("min");
        long width = (long)max - min;
        if (width > Int32.MaxValue) throw new NotSupportedException("unverified wide range");
        if (width < 2) return min; // Native short-circuit, including width 1.
        return unchecked((int)(Sample() * (int)width) + min);
    }
}

static class Program {
    static string Doubles(double[] values) {
        string[] parts = new string[values.Length];
        for (int i = 0; i < parts.Length; i++)
            parts[i] = values[i].ToString("R", CultureInfo.InvariantCulture);
        return "[" + String.Join(",", parts) + "]";
    }
    static string Ints(int[] values) {
        string[] parts = new string[values.Length];
        for (int i = 0; i < parts.Length; i++)
            parts[i] = values[i].ToString(CultureInfo.InvariantCulture);
        return "[" + String.Join(",", parts) + "]";
    }
    public static void Main() {
        int[] seeds = {0, 1, -1, 42, -42, 1808733512, Int32.MinValue, Int32.MaxValue};
        int[] maxima = {0, 1, 2, 10, 100, Int32.MaxValue, 0, 99};
        int[] minima = {5, 5, -10, -10, 0, 100, Int32.MinValue};
        int[] rangeMaxima = {5, 6, -9, 10, 100, 1000, -1};
        StringBuilder output = new StringBuilder();
        output.Append("{\"oracle_scope\":\"independent C# translation of native pseudocode; not game runtime\",\"vectors\":[");
        for (int n = 0; n < seeds.Length; n++) {
            if (n != 0) output.Append(',');
            LegacyReference a = new LegacyReference(seeds[n]);
            LegacyReference b = new LegacyReference(seeds[n]);
            LegacyReference c = new LegacyReference(seeds[n]);
            LegacyReference d = new LegacyReference(seeds[n]);
            Random system = new Random(seeds[n]);
            int[] integers = new int[128], bounded = new int[maxima.Length], systemInts = new int[8];
            int[] ranged = new int[minima.Length];
            double[] samples = new double[16];
            for (int i = 0; i < integers.Length; i++) integers[i] = a.Next();
            for (int i = 0; i < samples.Length; i++) samples[i] = b.Sample();
            for (int i = 0; i < maxima.Length; i++) bounded[i] = c.Next(maxima[i]);
            for (int i = 0; i < minima.Length; i++) ranged[i] = d.NextRange(minima[i], rangeMaxima[i]);
            for (int i = 0; i < systemInts.Length; i++) systemInts[i] = system.Next();
            output.Append("{\"seed\":" + seeds[n].ToString(CultureInfo.InvariantCulture));
            output.Append(",\"next\":" + Ints(integers));
            output.Append(",\"sample\":" + Doubles(samples));
            output.Append(",\"maxima\":" + Ints(maxima));
            output.Append(",\"bounded\":" + Ints(bounded));
            output.Append(",\"minima\":" + Ints(minima));
            output.Append(",\"range_maxima\":" + Ints(rangeMaxima));
            output.Append(",\"ranged\":" + Ints(ranged));
            output.Append(",\"next_after_ranges\":" + d.Next().ToString(CultureInfo.InvariantCulture));
            output.Append(",\"system_random_next\":" + Ints(systemInts) + "}");
        }
        output.Append("]}");
        Console.WriteLine(output.ToString());
    }
}
