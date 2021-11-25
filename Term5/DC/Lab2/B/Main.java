package com.company;

import java.util.ArrayList;
import java.util.Random;


class MilitaryUnit {
    public MilitaryUnit(int gc) {
        goodsCount = gc;
    }

    private void print(String event, int price) {
        System.out.printf(format, storage.size(), street.size(),
            truckCounter, event, price, totalPrice);
    }

    private static void sleep(long time) {
        try {Thread.sleep(time);}
        catch (InterruptedException e) { e.printStackTrace(); }
    }

    private void storageToStreet() {
        while (!storage.isEmpty()) {
            sleep(200);
            var g = storage.remove(storage.size() - 1);
            print("Storage -> Street", g.getPrice());
            street.put(g);
        }
        street.close();
    }

    private void streetToTruck() {
        while (!street.isClosed() || !street.isEmpty()) {
            sleep(600);
            truckCounter++;
            var g = street.take();
            print("Street -> Truck", g.getPrice());
            truck.put(g);
        }
        truck.close();
    }

    private void countPrice() {
        while (!truck.isClosed() || !truck.isEmpty()) {
            sleep(800);
            var g = truck.take();
            totalPrice += g.getPrice();
            print("Counted", g.getPrice());
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

        System.out.println("Starting work:");
        System.out.printf(format, "Storage", "Street",
            "Truck", "Event", "Price", "Total Price");
        System.out.println("├─────────┼─────────┼──────────╬─" +
            "──────────────────────┼───────────┼────────────────┤");

        print("Started", 0);

        new Thread(this::storageToStreet).start();
        new Thread(this::streetToTruck).start();
        new Thread(this::countPrice).start();
    }

    private final String format = "│%8s │%8s │%8s  ║  %20s │%10s │%15s │%n";

    private final ArrayList<Good> storage = new ArrayList<>();
    private final BlockingQueue<Good> street = new BlockingQueue<>();
    private final BlockingQueue<Good> truck = new BlockingQueue<>();
    private final int goodsCount;

    private int totalPrice = 0;
    private int truckCounter = 0;


    static public class Good {
        private final int price;
        public Good(int p) {
            price = p;
        }
        public int getPrice() {
            return price;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        MilitaryUnit mu = new MilitaryUnit(10);
        mu.runWork();
    }
}
