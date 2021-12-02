import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;

public class Main {
  // c1 and c2 - needed components
  static void smoker(String name, Semaphore c1, Semaphore c2) {
    c1.await();
    c2.await();

    System.out.println(name + " is smoking");

    try {
      Thread.sleep(1000);
    } catch (InterruptedException e) {e.printStackTrace();}

    System.out.println(name + " finished");
  }


  public static void main(String[] args) {
    Semaphore tobacco = new Semaphore();
    Semaphore paper = new Semaphore();
    Semaphore matches = new Semaphore();

    new Thread(()->smoker("Smoker with paper", tobacco, matches)).start();
    new Thread(()->smoker("Smoker with tobacco", paper, matches)).start();
    new Thread(()->smoker("Smoker with matches", tobacco, paper)).start();

    while (!Thread.interrupted()) {
      int a = ThreadLocalRandom.current().nextInt(3);
      if (a == 0) {
        System.out.println("Agent put paper on the table");
        paper.signal();
      } else if (a == 1) {
        System.out.println("Agent put tobacco on the table");
        tobacco.signal();
      } else {
        System.out.println("Agent put matches on the table");
        matches.signal();
      }

      try {
        Thread.sleep(1000);
      } catch (InterruptedException e) {e.printStackTrace();}
    }
  }
}
