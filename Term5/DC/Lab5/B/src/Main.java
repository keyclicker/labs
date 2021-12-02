import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

class StrChanger {
  private static final ThreadLocalRandom rand = ThreadLocalRandom.current();
  private static final int strCount = 4, minEquals = 3;

  static private String genStr(int strSize) {
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < strSize; i++) {
      var rc = rand.nextInt(4);
      if (rc == 0) sb.append("A");
      else if (rc == 1) sb.append("B");
      else if (rc == 2) sb.append("C");
      else if (rc == 3) sb.append("D");
    }
    return sb.toString();
  }

  private boolean stopped = false;
  private Barrier barrier;
  private ArrayList<String> strings;

  StrChanger(int strSize) {
    barrier = new Barrier(strCount, this::checker);
    strings = new ArrayList<>();

    for (int i = 0; i < strCount; i++)
      strings.add(genStr(strSize));
  }

  public void checker() {
    var map = new HashMap<Integer, Integer>();

    for (int i = 0; i < strings.size(); ++i) {
      var abCount = 0;
      for (var ch : strings.get(i).toCharArray()) {
        if (ch == 'A' || ch == 'B') abCount++;
      }
      System.out.println("String-" + i + ": A/B count - " + abCount);
      var oldCnt = map.get(abCount);
      map.put(abCount, oldCnt == null ? 1 : oldCnt + 1);
    }
    var max = Collections.max(map.entrySet(), Map.Entry.comparingByValue()).getValue();

    System.out.println("Max count of equal counts: " + max + "\n");

    if (max >= minEquals)
      stopped = true;

    try {
      Thread.sleep(200);
    } catch (Exception e) {e.printStackTrace();}
  }

  public void changer(int strIndex) {
    String str = strings.get(strIndex);

    while (!stopped) {
      var pos = rand.nextInt(str.length());
      var ch = str.charAt(pos);

      if (ch == 'A') ch = 'C';
      else if (ch == 'C') ch = 'A';
      else if (ch == 'B') ch = 'D';
      else if (ch == 'D') ch = 'B';

      String oldStr = new String(str);
      strings.set(strIndex,
          str.substring(0,pos) + ch + str.substring(pos + 1));

      System.out.println(Thread.currentThread().getName() +
          ": " + oldStr + " -> " + str);

      try {
        Thread.sleep(500);
        barrier.await();
      } catch (Exception e) {e.printStackTrace();}
    }
  }

  public void start() {
    for (int i = 0; i < strings.size(); i++) {
      int finalI = i;
      new Thread(()->changer(finalI)).start();
    }
  }
}

public class Main {
  public static void main(String[] args) {
    new StrChanger(10).start();
  }
}
