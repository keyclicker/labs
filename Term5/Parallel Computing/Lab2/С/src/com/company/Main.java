package com.company;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.RecursiveTask;


class FistPath {
    private Random rand = new Random(System.currentTimeMillis());
    private final ArrayList<Monk> monks = new ArrayList<>();

    class Monk {
        static private final String[] names = {"Lorem", "Ipsum", "Dolor", "Sit", "Amet", "Consectetur", "Adipiscing", "Elit", "Sed", "Do", "Eiusmod", "Tempor", "Incididunt", "Ut", "Labore", "Et", "Dolore", "Magna", "Aliqua", "Ut", "Enim", "Ad", "Minim", "Veniam", "Quis", "Nostrud", "Exercitation", "Ullamco", "Laboris", "Nisi", "Ut", "Aliquip", "Ex", "Ea", "Commodo", "Consequat", "Duis", "Aute", "Irure", "Dolor", "In", "Reprehenderit", "In", "Voluptate", "Velit", "Esse", "Cillum", "Dolore", "Eu", "Fugiat", "Nulla", "Pariatur", "Excepteur", "Sint", "Occaecat", "Cupidatat", "Non", "Proident", "Sunt", "In", "Culpa", "Qui", "Officia", "Deserunt", "Mollit", "Anim", "Id", "Est", "Laborum"};

        private final String name;
        private final float power;

        public String getName() {
            return name;
        }

        public float getPower() {
            return power;
        }

        public Monk() {
            power = rand.nextFloat() * 1000;
            name = names[rand.nextInt(names.length)] + " " +
                names[rand.nextInt(names.length)];
        }

        @Override
        public String toString() {
            return  "Name: " + name + "Power: " + power;
        }
    }

    class Round extends RecursiveTask<Monk> {
        private final ArrayList<Monk> monks;
        private final int beg, end;

        public Round(ArrayList<Monk> m) {
            monks = m;
            beg = 0;
            end = m.size();
        }

        public Round(ArrayList<Monk> m, int b, int e) {
            monks = m;
            beg = b;
            end = e;
        }

        private Monk fight(Monk m1, Monk m2) {
            if (m1.getPower() > m2.getPower()) {
                return m1;
            } else if (m1.getPower() < m2.getPower()) {
                return m2;
            } else {
                if (rand.nextInt(2) == 0)
                    return m1;
                else
                    return m2;
            }
        }

        @Override
        protected Monk compute() {
            if (end - beg == 0) {
              return new Monk();
            } else if (end - beg == 1) {
                return monks.get(beg);
            } else if (end - beg == 2) {
                return fight(monks.get(beg), monks.get(end - 1));
            } else {
                var mid = monks.size() / 2;

                var r1 = new Round(monks, beg, mid + 1);
                r1.fork();

                var r2 = new Round(monks, mid, end);

                return fight(r2.compute(), r1.join());
            }
        }
    }

    public FistPath(int mc) {
        System.out.println("Participants:");
        for (int i = 0; i < mc; i++) {
            var m = new Monk();
            monks.add(m);
            System.out.println(i + ": " + m);
        }
    }

    public void start() {
        var finalRound = new Round(monks);
        System.out.println("Winner: " + finalRound.compute());
    }
}

public class Main {
    public static void main(String[] args) {
        var fp = new FistPath(10);
        fp.start();
    }
}
