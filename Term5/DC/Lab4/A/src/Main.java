import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.locks.ReentrantReadWriteLock;

class PhoneBook {
  ReentrantReadWriteLock lock = new ReentrantReadWriteLock();
  File file;

  interface Condition {
    boolean check(Record record);
  }

  private void find(String printStr, Condition cond) {
    Record rec = null;

    lock.readLock().lock();
    try {
      var in = new Scanner(file);
      while (in.hasNextLine()) {
        Record tmpRec = Record.parse(in.nextLine());
        if (cond.check(tmpRec)) {
          rec = tmpRec;
          break;
        }
      }
      in.close();
    } catch (FileNotFoundException e) { e.printStackTrace(); }
    lock.readLock().unlock();

    if (rec != null)
      System.out.println(printStr + "\"\n\tresult: \"" + rec + "\"");
    else
      System.out.println(printStr + "\"\n\tNot Found!");

    try {
      Thread.sleep(1000);
    } catch (InterruptedException e) { e.printStackTrace(); }
  }

  private void findName() {
    while (!Thread.interrupted()) {
      var query = Record.randName();
      find("Name Search:\n\tquery: \"" + query,
          (Record rec) -> rec.name.contains(query));
    }
  }

  private void findPhone() {
    while (!Thread.interrupted()) {
      var query = Record.randNumberQuery();
      find("Number Search:\n\tquery: \"" + query,
          (Record rec) -> rec.phoneNumber.contains(query));
    }
  }


  private ArrayList<Record> readRecords(File file) {
    var recs = new ArrayList<Record>();
    lock.readLock().lock();
    try {
      var in = new Scanner(file);
      while (in.hasNextLine()) {
        recs.add(Record.parse(in.nextLine()));
      }
      in.close();
    } catch (Exception e) { e.printStackTrace(); }
    lock.readLock().unlock();
    return recs;
  }

  private void writeRecords(ArrayList<Record> recs, File file) {
    lock.writeLock().lock();
    try {
      var out = new FileWriter(file);
      for (var rec : recs) {
        out.write(rec.toString() + "\n");
      }
      out.close();
    } catch (Exception e) { e.printStackTrace(); }
    lock.writeLock().unlock();
  }

  private void editor() {
    var rand = ThreadLocalRandom.current();
    while (!Thread.interrupted()) {
      var recs = readRecords(file);
      int action = rand.nextInt(2);

      if (action == 0 && !recs.isEmpty()) {
        var index = rand.nextInt(recs.size());
        System.out.println("Removing:" +
            "\n\tindex: " + index +
            "\n\trecord: " + recs.remove(index));
      }
      else {
        var index = recs.isEmpty() ? 0 : rand.nextInt(recs.size());
        var rec = Record.randRecord();
        recs.add(index, rec);

        System.out.println("Adding:" +
            "\n\tindex: " + index +
            "\n\trecord: " + rec);
      }

      writeRecords(recs, file);

      try {
        Thread.sleep(1000);
      } catch (InterruptedException e) { e.printStackTrace(); }
    }
  }


  public void start() {
    new Thread(this::findName).start();
    new Thread(this::findPhone).start();
    new Thread(this::editor).start();
  }

  PhoneBook(String file) {
    this.file = new File(file);
  }
}

public class Main {
  public static void main(String[] args) {
    new PhoneBook("phonebook.txt").start();
  }
}
