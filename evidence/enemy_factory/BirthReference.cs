// Independent C# port of the selected BORN countdown/dispatch ordering.
// This executable is our own reference, not the game or a client oracle.
using System;
using System.Globalization;
using System.IO;
class BirthReference {
    static void Main(string[] args) {
        foreach (string line in File.ReadAllLines(args[0])) {
            if (String.IsNullOrWhiteSpace(line)) continue;
            string[] p=line.Split(',');
            long remaining=Int64.Parse(p[1],CultureInfo.InvariantCulture);
            long dt=Int64.Parse(p[2],CultureInfo.InvariantCulture);
            int ticks=Int32.Parse(p[3],CultureInfo.InvariantCulture), state=6, moves=0;
            for(int frame=1;frame<=ticks;frame++) {
                // StateMachine.Tick uses the state selected at Tick entry;
                // entering MOVE does not invoke MOVE.OnTick on this frame.
                if(state==6) {
                    remaining=unchecked(remaining-dt);
                    // Original 185ed91e0: CMP RCX,RDX; SETLE AL; RET.
                    if(remaining<=0) state=1;
                } else if(state==1) moves++;
                Console.WriteLine(p[0]+","+frame+","+state+","+remaining+","+moves);
            }
        }
    }
}
