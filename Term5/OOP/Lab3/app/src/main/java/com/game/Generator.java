package com.game;

import java.util.Random;

public class Generator {
  static int[][][] bricks = {{
      {1}
  },{
      {1,1,1},
  },{
      {1,1,1,1},
  },{
      {1,1,1},
      {1,1,1},
      {1,1,1}
  },{
      {1,1,1},
      {1,1,1}
  },{
      {1,0,0},
      {1,1,1}
  },{
      {1,0,0},
      {1,1,1}
  },{
      {0,0,1},
      {1,1,1}
  },{
      {1,1},
      {1,1}
  },{
      {0,1,1},
      {1,1,0}
  }, {
      {0,1,0},
      {1,1,1}
  },{
      {1,1,0},
      {0,1,1}
  }};

  private static final Random rand = new Random(System.currentTimeMillis());

  private static int[][] rotate(int[][] b) {
    final int M = b.length;
    final int N = b[0].length;

    int[][] ret = new int[N][M];
    for (int r = 0; r < M; r++) {
      for (int c = 0; c < N; c++) {
        ret[c][M - 1 - r] = b[r][c];
      }
    }
    return ret;
  }

  public static int[][] generate() {
    int[][] b = bricks[rand.nextInt(bricks.length)];
    int rotateCount = rand.nextInt(4);

    for (int k = 0; k < rotateCount; k++) {
      b = rotate(b);
    }
    return b;
  }
}
