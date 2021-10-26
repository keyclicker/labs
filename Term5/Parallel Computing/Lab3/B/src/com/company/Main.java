package com.company;

import java.util.Queue;
import java.util.Random;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

class BarberShop {
  private static final Random rand = new Random(System.currentTimeMillis());




  private void barber() {

  }

  private void customer(int id) {

  }

  private void customerProducer() {
    while (true) {
      new Thread(new Runnable() {
        @Override
        public void run() {
          try {
            customerProducer();
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }
      }).start();
    }
  }

  public void start() {
    new Thread(new Runnable() {
      @Override
      public void run() {
        try {
          barber();
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
    }).start();

    new Thread(new Runnable() {
      @Override
      public void run() {
        try {
          customerProducer();
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
    }).start();
  }
}

public class Main {
  public static void main(String[] args) {
    var bs = new BarberShop();
    bs.start();
  }
}
