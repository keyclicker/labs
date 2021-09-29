package com.company;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.RecursiveTask;


class FistPath {
    private static final Random rand = new Random(System.currentTimeMillis());
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
            return  "Name: '" + name + "', Power: " + power;
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

        private static Monk fight(Monk m1, Monk m2) {
            if (m1 == m2) return m1;

            Monk winner;
            if (m1.getPower() > m2.getPower()) {
                winner = m1;
            } else if (m1.getPower() < m2.getPower()) {
                winner = m2;
            } else {
                if (rand.nextInt(2) == 0)
                    winner = m1;
                else
                    winner = m2;
            }

            System.out.println("Fight: <" + m1 + "> vs <" +
                m2 + "> Winner: "  + winner);

            return winner;
        }

        @Override
        protected Monk compute() {
            if (end - beg == 2) {
                return fight(monks.get(beg), monks.get(end - 1));
            }
            else {
                var mid = (beg + end) / 2;

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
        System.out.println();
    }

    public void start() {
        var finalRound = new Round(monks);
        System.out.println("\nFist Path Winner:\n" + finalRound.compute());
    }
}

public class Main {
    public static void main(String[] args) {
        var fp = new FistPath(500);
        fp.start();
    }
}
