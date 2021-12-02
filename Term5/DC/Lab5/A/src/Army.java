import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicInteger;

public class Army {
  static final int ThreadCount = 4;

  private final int size;
  private final Rookie head;
  private CyclicBarrier barrier;
  private final AtomicInteger threadsFinished = new AtomicInteger(0);

  Army(int size) {
    this.size = size;
    head = new Rookie();
    var cur = head;
    for (int i = 0; i < size - 1; i++) {
      cur.right = new Rookie(cur, null);
      cur = cur.right;
    }
  }

  public String toString() {
    StringBuilder res = new StringBuilder();
    for (var i = head; i != null; i = i.right) {
      res.append(i);
    }
    return res.toString();
  }

  public Rookie getRookie(int index) {
    if (index >= size)
      throw new IndexOutOfBoundsException(index);

    Rookie cur = head;
    for (int i = 0; i <= index; i++)
      cur = cur.right;
    return cur;
  }

  public void orderSection(Rookie begin, Rookie end) {
    while (!Thread.interrupted()) {
      boolean decision = false;
      for (var i = begin; i != end; i = i.right) {
        if (i.makeDecision()) decision = true;
      }

      if (!decision)
        threadsFinished.incrementAndGet();

      try {
        barrier.await();
      } catch (Exception e) {e.printStackTrace();}

      for (var i = begin; i != end; i = i.right) {
        i.performDecision();
      }
    }
  }

  public void order() {
    var chunkSize = size / ThreadCount;

    barrier = new CyclicBarrier(ThreadCount, () -> {
      System.out.println(this);
      if (threadsFinished.get() >= ThreadCount)
        System.exit(0);
      threadsFinished.set(0);
    });

    for (int i = 0; i < ThreadCount - 1; i++) {
      var begin = getRookie(i * chunkSize);
      var end = getRookie((i + 1) * chunkSize);
      new Thread(() -> orderSection(begin, end)).start();
    }
    new Thread(() -> orderSection(
        getRookie((ThreadCount - 1) * chunkSize), null)).start();
  }
}