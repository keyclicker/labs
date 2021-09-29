package com.company;

import java.awt.desktop.SystemEventListener;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;


class BlockingQueue<T> {
    private Queue<T> queue = new LinkedList<>();

    public synchronized void put(T value) {
        queue.add(value);
        notifyAll(); //empty
    }

    public synchronized T take() throws InterruptedException {
        if (queue.isEmpty()) {
            wait(); //empty
        }
        return queue.remove();
    }

    public boolean isEmpty()  {
        return queue.isEmpty();
    }

    public int size() {
        return queue.size();
    }
}

class MilitaryUnit {
    static public class Good {
        private final int price;
        public Good(int p) {
            price = p;
        }
        public int getPrice() {
            return price;
        }
    }

    private int goodsCount;

    private ArrayList<Good> storage = new ArrayList<>();
    private BlockingQueue<Good> street = new BlockingQueue<>();
    private ArrayList<Good> truck = new ArrayList<>();

    private final Object nothingToCount = new Object();

    private int totalPrice = 0;

    public MilitaryUnit(int gc) {
        goodsCount = gc;
    }

    private String getState() {
        return "[" + storage.size() + "] -> " +
            "[" + street.size() + "] -> " +
            "[" + truck.size() + "]: ";
    }

    private void storageToStreet() throws InterruptedException {
        while (!storage.isEmpty()) {
            Thread.sleep(1000);
            var g = storage.remove(storage.size() - 1);
            street.put(g);

            System.out.println(getState() +
                "Storage -> Street, price: " + g.getPrice());
        }
    }

    private void streetToTruck() throws InterruptedException {
        while (!storage.isEmpty() || !street.isEmpty()) {
            Thread.sleep(600);
            var g = street.take();
            truck.add(g);

            synchronized (nothingToCount) {
                nothingToCount.notifyAll();
            }

            System.out.println(getState() +
                "Street -> Truck, price: " + g.getPrice());
        }
    }

    private void countPrice() throws InterruptedException {
        int i = 0;
        while (!storage.isEmpty() || !street.isEmpty() || i < truck.size()) {
            if (i < truck.size()) {
                Thread.sleep(500);
                totalPrice += truck.get(i).getPrice();

                System.out.println( getState() + "Counted, i: " + i +
                        ", price: " + truck.get(i).getPrice() +
                        ", total price: " + totalPrice);
                i++;
            } else {
                synchronized (nothingToCount) {
                    nothingToCount.wait();
                }
            }
        }
    }

    public void runWork() {
        Random rand = new Random(System.currentTimeMillis());
        int totalPrice = 0;

        for (int i = 0; i < goodsCount; i++) {
            int price = rand.nextInt(50000) + 500;
            storage.add(new Good(price));
            totalPrice += price;
        }

        System.out.println("Total count: " + goodsCount +
            ", total price: " + totalPrice);

        System.out.println("Starting work:\n" + getState());

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    storageToStreet();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    streetToTruck();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    countPrice();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}



public class Main {
    public static void main(String[] args) {
        MilitaryUnit mu = new MilitaryUnit(10);
        mu.runWork();
    }
}
