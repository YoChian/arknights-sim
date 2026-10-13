// Independent C# translation of the statically recovered midpoint Quicksort.
// The host List.Sort output is a comparison, not an Arknights client oracle.
using System;
using System.Collections.Generic;
using System.IO;
using System.Web.Script.Serialization;

public sealed class QueueItem {
    public int id;
    public float time;
}

public static class QueueSortReference {
    static void RecoveredSort(QueueItem[] records, int left, int right) {
        while (left < right) {
            int low = left;
            int high = right;
            float pivot = records[left + (right - left) / 2].time;
            while (true) {
                while (low < right && records[low].time.CompareTo(pivot) < 0) ++low;
                while (high > left && pivot.CompareTo(records[high].time) < 0) --high;
                if (low > high) break;
                QueueItem temporary = records[low];
                records[low] = records[high];
                records[high] = temporary;
                ++low;
                --high;
            }
            if (left < high) RecoveredSort(records, left, high);
            if (low >= right) return;
            left = low;
        }
    }

    static float FromBits(uint bits) {
        return BitConverter.ToSingle(BitConverter.GetBytes(bits), 0);
    }
    static uint Bits(float value) {
        return BitConverter.ToUInt32(BitConverter.GetBytes(value), 0);
    }
    static int[] Ids(IList<QueueItem> records) {
        int[] result = new int[records.Count];
        for (int i=0; i<records.Count; ++i) result[i] = records[i].id;
        return result;
    }

    public static int Main(string[] args) {
        if (args.Length != 1) throw new ArgumentException("Expected output JSON path");
        int[] lengths = new int[] { 0,1,2,3,4,8,15,16,17,20,24,31,32,33,48,64,127,128,129 };
        uint[] special = new uint[] { 0x7fc00001u,0x7f800000u,0x00000000u,0x80000000u,0xff800000u,0xbf800000u,0x3f800000u,0xffc00023u,0x3f800001u };
        string[] names = new string[] { "all_equal", "ascending", "descending", "repeated_5", "lcg_duplicates", "binary32_rounding", "nan_infinity_signedzero", "single_outlier" };
        List<object> cases = new List<object>();
        foreach (int length in lengths) {
            for (int pattern=0; pattern<names.Length; ++pattern) {
                QueueItem[] input = new QueueItem[length];
                uint[] bits = new uint[length];
                uint state = 0x8d90305fu;
                for (int i=0; i<length; ++i) {
                    float time;
                    switch (pattern) {
                    case 0: time = 3.25f; break;
                    case 1: time = i; break;
                    case 2: time = length-i; break;
                    case 3: time = (i%5)-2; break;
                    case 4: state = unchecked(state*1664525u+1013904223u); time = (int)(state%11u)-5; break;
                    case 5: time = 1f + (i%3)*(1f/16777216f); break;
                    case 6: time = FromBits(special[i%special.Length]); break;
                    default: time = i==length/3 ? -7f : 4f; break;
                    }
                    input[i] = new QueueItem { id=i, time=time };
                    bits[i] = Bits(time);
                }
                QueueItem[] recovered = (QueueItem[])input.Clone();
                if (length>1) RecoveredSort(recovered, 0, length-1);
                List<QueueItem> host = new List<QueueItem>(input);
                host.Sort(delegate(QueueItem a, QueueItem b) { return a.time.CompareTo(b.time); });
                cases.Add(new Dictionary<string,object> {
                    {"name",names[pattern]+"_"+length}, {"pattern",names[pattern]}, {"length",length},
                    {"keys_binary32_bits",bits}, {"recovered_ids",Ids(recovered)}, {"host_list_sort_ids",Ids(host)}
                });
            }
        }
        List<object> compareCases = new List<object>();
        for (int i=0; i<special.Length; ++i) {
            for (int j=0; j<special.Length; ++j) {
                compareCases.Add(new Dictionary<string,object> {
                    {"left_bits",special[i]}, {"right_bits",special[j]},
                    {"comparison",FromBits(special[i]).CompareTo(FromBits(special[j]))}
                });
            }
        }
        var document = new Dictionary<string,object> {
            {"kind","independent C# reconstruction reference; not game oracle"},
            {"framework_version",Environment.Version.ToString()},
            {"algorithm_entry","0x184547860"}, {"target_sha256","583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5"},
            {"cases",cases}, {"single_compare_to_cases",compareCases}
        };
        var serializer = new JavaScriptSerializer();
        serializer.MaxJsonLength = 10*1024*1024;
        File.WriteAllText(args[0], serializer.Serialize(document));
        Console.WriteLine("Wrote "+cases.Count+" ordering cases and "+compareCases.Count+" Single.CompareTo cases");
        return 0;
    }
}
