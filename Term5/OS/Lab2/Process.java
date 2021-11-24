public class Process implements Comparable<Process> {
  private static int next_id = 0;
  public int id, cputime, ioblocking,
      cpudone, ionext, numblocked;

  public Process(int cputime, int ioblocking) {
    this.id = next_id++;
    this.cputime = cputime;
    this.ioblocking = ioblocking;
  }

  @Override
  public int compareTo(Process process) {
    return this.cputime - process.cputime;
  }

  public String format(String format) {
    return String.format(format,
        id, cputime + " ms", ioblocking + " ms",
        cpudone + " ms", numblocked + " times");
  }

}
