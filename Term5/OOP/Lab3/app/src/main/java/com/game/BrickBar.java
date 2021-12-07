package com.game;

public class BrickBar {
  int[][][] bricks;

  BrickBar(int size) {
    bricks = new int[size][][];
    for (int i = 0; i < size; i++)
      bricks[i] = BrickGenerator.generate();
  }

  public int[][] get(int index) {
    return bricks[index];
  }

  public void remove(int index) {
    if (index >= 0 && index < bricks.length)
      bricks[index] = BrickGenerator.generate();
  }
}
