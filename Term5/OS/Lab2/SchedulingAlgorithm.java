// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

import java.util.Vector;
import java.io.*;

public class SchedulingAlgorithm {

  public static Results Run(int runtime, Vector processVector, Results result) {
    int i = 0;
    int comptime = 0;
    int currentProcess = 0;
    int previousProcess = 0;
    int size = processVector.size();
    int completed = 0;
    String resultsFile = "Summary-Processes";

    result.schedulingType = "Batch (Nonpreemptive)";
    result.schedulingName = "First-Come First-Served";


    String format = "%9s%18s%s";
    String processFormat = "%12s%15s%17s%15s%n";

    try {
      PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
      sProcess process = (sProcess) processVector.elementAt(currentProcess);

      out.printf("%9s%18s" + processFormat,
          "Process #", "Event", "CPU Time", "IO Blocking",
          "CPU Completed", "CPU Blocked");

      out.printf(format, currentProcess, "registered...", process.format(processFormat));

      while (comptime < runtime) {
        if (process.cpudone == process.cputime) {
          completed++;
          out.printf(format, currentProcess, "completed...", process.format(processFormat));

          if (completed == size) {
            result.compuTime = comptime;
            out.close();
            return result;
          }
          for (i = size - 1; i >= 0; i--) {
            process = (sProcess) processVector.elementAt(i);
            if (process.cpudone < process.cputime) {
              currentProcess = i;
            }
          }
          process = (sProcess) processVector.elementAt(currentProcess);
          out.printf(format, currentProcess, "registered...", process.format(processFormat));
        }

        if (process.ioblocking == process.ionext) {
          out.printf(format, currentProcess, "I/O blocked...", process.format(processFormat));

          process.numblocked++;
          process.ionext = 0;
          previousProcess = currentProcess;

          for (i = size - 1; i >= 0; i--) {
            process = (sProcess) processVector.elementAt(i);
            if (process.cpudone < process.cputime && previousProcess != i) {
              currentProcess = i;
            }
          }

          process = (sProcess) processVector.elementAt(currentProcess);
          out.printf(format, currentProcess, "registered...", process.format(processFormat));
        }

        process.cpudone++;
        if (process.ioblocking > 0) {
          process.ionext++;
        }

        comptime++;
      }
      out.close();
    } catch (IOException e) { /* Handle exceptions */ }

    result.compuTime = comptime;
    return result;
  }
}
