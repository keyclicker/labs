public class Barier {
  private final int parties;
  private final Runnable barrierAction;
  private int counter;


  Barier(int parties, Runnable barrierAction) {
    this.parties = parties;
    this.counter = parties;
    this.barrierAction = barrierAction;
  }

  synchronized private void action() {
    barrierAction.run();
    counter = parties;
    notifyAll();
  }

  synchronized public void await() throws InterruptedException {
    counter--;
    if (counter == 0)  {
      action();
    } else {
      this.wait();
    }
  }
}
