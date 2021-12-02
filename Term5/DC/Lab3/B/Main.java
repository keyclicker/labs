package com.company;

import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.Semaphore;

class BarberShop {
  private LinkedBlockingQueue<Customer> queue = new LinkedBlockingQueue<>();

  static class Customer {
    Semaphore trimmingFinished = new Semaphore(0);
    public final int id;

    Customer(int id) {
      this.id = id;
      System.out.println("Customer " + id + " arrived");
      new Thread(this::run).start();
    }

    private void run(){
      try {
        trimmingFinished.acquire();
        System.out.println("Customer " + id + " leaves");
      } catch (InterruptedException e) {}
    }

    public void trim() throws InterruptedException {
      System.out.println("Barber is trimming " + id);
      Thread.sleep(5000);
      trimmingFinished.release();
      System.out.println("Barber finished trimming " + id);
    }
  }

  private void barber() {
    try {
      while (!Thread.interrupted()) {
        if (queue.isEmpty()) {
          System.out.println("Barber is sleeping");
        }
        var customer = queue.take();
        customer.trim();
      }
    } catch (InterruptedException e) {}
  }


  private void customerProducer() {
    try {
      for (int i = 0; !Thread.interrupted(); ++i) {
        Thread.sleep(4000);
        queue.put(new Customer(i));
      }
    } catch (InterruptedException e) {}
  }

  public void start() {
    new Thread(this::barber).start();
    new Thread(this::customerProducer).start();
  }
}

public class Main {
  public static void main(String[] args) {
    var bs = new BarberShop();
    bs.start();
  }
}
