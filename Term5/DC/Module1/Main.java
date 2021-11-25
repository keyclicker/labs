package com.company;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class Main {
    static class Bank {
        int cashbox = 500;
        int vault = 10000;

        //<CustomerId, Balance>
        Map<Integer, Integer> accounts = new HashMap<Integer, Integer>();
        BlockingQueue<ClientAction> queue = new LinkedBlockingDeque<ClientAction>();;

        private void observer () throws InterruptedException {
            while (!Thread.interrupted()) {
                synchronized (this) {
                    this.wait();
                    if (cashbox <= 0) {
                        int d = -cashbox + 500;
                        cashbox += d;
                        vault -= d;
                    }
                    if (cashbox > 1000) {
                        int d = cashbox - 1000 + 500;
                        cashbox -= d;
                        vault += d;
                    }
                }
            }
        }

        private void cashier() throws InterruptedException {
            while (!Thread.interrupted()) {
                var ca = queue.take();
                System.out.print("(Cashbox: " + cashbox + "; Vault: " + vault +
                        ") Serve client " + ca.id + "; balance: " + accounts.get(ca.id));

                synchronized (this) {
                    if (ca.type == ClientAction.Type.withdraw) {
                        System.out.println("; action: withdraw; amount: " + ca.amount);
                        accounts.put(ca.id, Math.max(0, accounts.get(ca.id) - ca.amount));
                        cashbox -= ca.amount;
                    } else if (ca.type == ClientAction.Type.topup) {
                        System.out.println("; action: topup; amount: " + ca.amount);
                        accounts.put(ca.id, accounts.get(ca.id) + ca.amount);
                        cashbox += ca.amount;
                    }
                    this.notifyAll();
                }
            }
        }

        public void getInQueue(ClientAction ca) throws InterruptedException {
            queue.put(ca);
        }

        Bank() {
            for (int i = 0; i < 1000; i++) {
                accounts.put(i, (int) (Math.random() * 400) + 400);
            }

            new Thread(()->{
                try {
                    observer();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }).start();
            new Thread(()->{
                try {
                    cashier();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }).start();
        }
    }

    static class ClientAction {
        enum Type {
            withdraw,
            topup,
        }
        int id;
        Type type;
        int amount;
    }

    private static Bank bank = new Bank();

    static void clientGenerator() throws InterruptedException {
        while (!Thread.interrupted()) {
            var ca = new ClientAction();
            ca.id = (int) (Math.random() * 1000);

            var type = (int) (Math.random() * 2);
            if (type == 0) ca.type = ClientAction.Type.withdraw;
            else if (type == 1) ca.type = ClientAction.Type.topup;

            ca.amount = (int) (Math.random() * 400);

            bank.getInQueue(ca);

            Thread.sleep((int) (Math.random() * 3000));
        }
    }

    public static void main(String[] args) throws InterruptedException {
        clientGenerator();
    }
}
