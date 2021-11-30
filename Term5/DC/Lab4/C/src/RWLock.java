import java.util.concurrent.atomic.AtomicBoolean;

public class RWLock {
  private int readCounter = 0;
  private int writeCounter = 0;

  synchronized public void readLock() {
    try {
      while (writeCounter > 0) wait();
      readCounter++;
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }

  synchronized public void readUnlock() {
    readCounter--;
    notifyAll();
  }

  synchronized public void writeLock() {
    try {
      while (writeCounter > 0 || readCounter > 0) wait();
      writeCounter++;
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }

  synchronized public void writeUnlock() {
    writeCounter--;
    notifyAll();
  }
}
