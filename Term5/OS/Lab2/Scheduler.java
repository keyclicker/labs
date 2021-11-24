// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

import java.util.*;
import java.io.*;

public class Scheduler {
  final String resultsFile = "files/Summary-Processes";
  final String format = "%15s%s";
  final String processFormat = "%5s%12s%15s%17s%15s%n";

  int runtime;
  ArrayList<Process> processes = new ArrayList<Process>();
  PrintStream out;

  private void register(Process p) {
    out.printf(format, "Registered", p.format(processFormat));
  }

  public int Run() {
    int comptime = 0;

    try {
      out = new PrintStream(new FileOutputStream(resultsFile));
      out.printf("%15s" + processFormat,
          "Event", "PID", "CPU Time", "IO Blocking",
          "CPU Completed", "CPU Blocked");


      TreeSet<Process> queue = new TreeSet<Process>(processes);
      Process current = queue.pollFirst();
      if (current != null) register(current);

      while (comptime < runtime && current != null) {
        current.cpudone++;
        if (current.ioblocking > 0) {
          current.ionext++;
        }
        comptime++;

        if (current.cpudone == current.cputime) {
          out.printf(format, "Completed", current.format(processFormat));

          current = queue.pollFirst();
          if (current != null) register(current);
        }
        else if (current.ioblocking == current.ionext) {
          current.numblocked++;
          current.ionext = 0;
          out.printf(format, "I/O blocked", current.format(processFormat));

          Process prev = current;
          current = queue.pollFirst();
          if (current != null) {
            queue.add(prev);
            register(current);
          }
          else {
            current = prev;
          }
        }
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }

    return comptime;
  }
}
