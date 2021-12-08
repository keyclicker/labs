package com.game;

import java.util.Random;

public class Grid {
  private static final Random rand = new Random(System.currentTimeMillis());

  int[][] grid;
  int size;
  int score = 0;

  Grid(int size) {
    this.size = size;
    restart();
  }

  private void step() {
    for (int i = 0; i < size; i++) {
      boolean v = true, h = true;
      for (int j = 0; j < size; j++) {
        if (grid[i][j] != 1) v = false;
        if (grid[j][i] != 1) h = false;
      }
      if (v)  {
        for (int j = 0; j < size; j++) grid[i][j] = 0;
        score += size;
      }
      if (h) {
        for (int j = 0; j < size; j++) grid[j][i] = 0;
        score += size;
      }
    }
  }

  private boolean in(int v) {
    return v >= 0 && v < size;
  }

  public boolean put(int[][] brick, int x, int y) {
    System.out.println(x + " " + y);
    int dx = brick.length;
    int dy = brick[0].length;

    if (in(x) && in(y) && in(x + dx - 1) && in(y + dy - 1)) {
      for (int i = 0; i < dx; i++) {
        for (int j = 0; j < dy; j++) {
          if (grid[x + i][y + j] > 0 && brick[i][j] > 0)
            return false;
        }
      }

      for (int i = 0; i < dx; i++) {
        for (int j = 0; j < dy; j++) {
          score += brick[i][j];
          grid[x + i][y + j] += brick[i][j];
        }
      }
      step();
      return true;
    }
    return false;
  }

  public void gen() {
    for (int i = 0; i < 5;) {
      if (put(Generator.generate(),
          rand.nextInt(size), rand.nextInt(size))) {
        i++;
      };
    }
//    grid[rand.nextInt(size)][rand.nextInt(size)] = 2;
//    grid[rand.nextInt(size)][rand.nextInt(size)] = 2;
  }

  public void restart() {
    grid = new int[size][size];
    for (int i = 0; i < size; i++) {
      grid[i] = new int[size];
      for (int j = 0; j < size; j++)
        grid[i][j] = 0; //rand.nextInt(2);
    }
    gen();
    score = 0;
  }
}
