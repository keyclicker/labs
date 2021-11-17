public class sProcess {
  public int cputime;
  public int ioblocking;
  public int cpudone;
  public int ionext;
  public int numblocked;

  public sProcess (int cputime, int ioblocking, int cpudone, int ionext, int numblocked) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.cpudone = cpudone;
    this.ionext = ionext;
    this.numblocked = numblocked;
  }

  public String toString() {
    return "(" + cputime + " " + ioblocking + " " + cpudone + " " + numblocked + ")";
  }
  public String format(String format) {
    return String.format(format,
            cputime + " ms", ioblocking + " ms",
            cpudone + " ms", numblocked + " times");
  }
}
