import java.util.ArrayList;

public class Main {
  static class Smoker {
    String name;
    Smoker(String name) {
      this.name = name;
      new Thread(this::run).start();
    }
    synchronized private void run() {
      try {
        while (!Thread.interrupted()) {
          wait();
          System.out.println(name + " is smoking");
          Thread.sleep(1000);
          System.out.println(name + " finished");
          notify();
        }
      } catch (InterruptedException e) {}
    }
  }

  static void agent(ArrayList<Smoker> smokers) {
    try {
      while (!Thread.interrupted()) {
        int index = (int) (Math.random() * smokers.size());
        var smoker = smokers.get(index);
        synchronized (smoker) {
          smoker.notify();
          smoker.wait();
        }
        Thread.sleep(1000);
      }
    } catch (InterruptedException e) {}
  }

  public static void main(String[] args) {
    var smokers = new ArrayList<Smoker>();
    smokers.add(new Smoker("Smoker with paper"));
    smokers.add(new Smoker("Smoker with tobacco"));
    smokers.add(new Smoker("Smoker with matches"));
    agent(smokers);
  }
}
