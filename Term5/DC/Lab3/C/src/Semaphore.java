import java.util.concurrent.atomic.AtomicInteger;

public class Semaphore {
  private int counter;

  synchronized public void await() {
    try {
      while (counter == 0)
        this.wait();
    } catch (InterruptedException e) { e.printStackTrace();}
    counter--;
  }

  synchronized public void signal() {
    counter++;
    this.notifyAll();
  }
}
