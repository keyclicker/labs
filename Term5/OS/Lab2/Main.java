// This file contains the main() function for the Scheduling
// simulation.  Init() initializes most of the variables by
// reading from a provided file.  SchedulingAlgorithm.Run() is
// called from main() to run the simulation.  Summary-Results
// is where the summary results are written, and Summary-Processes
// is where the process scheduling summary is written.

// Created by Alexander Reeder, 2001 January 06

import java.io.*;
import java.util.*;

public class Main {
  private static Scheduler sc;

  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Usage: 'java Scheduling <INIT FILE>'");
      System.exit(-1);
    }

    sc = new Scheduler();
    Init(args[0]);

    int time = sc.Run();
    printRes(time);
  }

  private static void Init(String file) {
    File f = new File(file);

    try {
      DataInputStream in = new DataInputStream(new FileInputStream(f));

      String line;
      while ((line = in.readLine()) != null) {
        if (line.startsWith("process")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();

          Process p = new Process(Integer.parseInt(st.nextToken()),
                                  Integer.parseInt(st.nextToken()));
          sc.processes.add(p);
        }

        if (line.startsWith("runtime")) {
          StringTokenizer st = new StringTokenizer(line);
          st.nextToken();
          sc.runtime = Integer.parseInt(st.nextToken());
        }
      }
      in.close();
    } catch (IOException e) { /* Handle exceptions */ }
  }


  private static void printRes(int time) {
    try {
      //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
      PrintStream out = new PrintStream(new FileOutputStream("files/Summary-Results"));
      out.println("Simulation Run Time: " + time);

      String processFormat = "%5s%12s%15s%17s%15s%n";

      out.printf(processFormat,
          "ID", "CPU Time", "IO Blocking",
          "CPU Completed", "CPU Blocked");

      for (Process p : sc.processes) {
        out.print(p.format(processFormat));
      }

      out.close();
    } catch (IOException e) { /* Handle exceptions */ }

    System.out.println("Completed.");
  }
}

