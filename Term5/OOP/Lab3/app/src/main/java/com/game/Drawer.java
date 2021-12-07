package com.game;

import android.content.res.Resources;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

public class Drawer {
  static final int TOP_MARGIN = 250;
  static final float BFS = 50; // bomb font size

  static class Assets {
    Paint tileP;
    Paint brickP;
    Paint brickPaint;
    Paint bombTextP;
    
    static Paint getPaint(int c, Paint.Style s) {
      Paint p = new Paint();
      p.setColor(c);
      p.setStyle(s);
      return p;
    }

    Assets(Resources res) {
      tileP = getPaint(Color.GRAY, Paint.Style.STROKE);
      tileP.setStrokeWidth(5);
      brickP = getPaint(Color.rgb(240,200,50), Paint.Style.FILL);
      brickPaint = getPaint(Color.RED, Paint.Style.FILL);
      bombTextP = getPaint(Color.BLACK, Paint.Style.FILL);
      bombTextP.setTextSize(BFS);
    }
  }

  static Assets assets;

  static public void drawTile(Canvas canvas, Vect p, float sz) {
    canvas.drawRect(p.x, p.y, p.x + sz, p.y + sz, assets.tileP);
  }

  static public void drawBrickTile(Canvas canvas, Vect p, float sz) {
    canvas.drawRect(p.x, p.y, p.x + sz, p.y + sz, assets.brickP);
  }

  static public void drawBomb(Canvas canvas, Vect p, float sz, int time) {
    canvas.drawCircle(p.x + sz / 2, p.y + sz / 2, sz / 3, assets.brickPaint);

    canvas.drawText(String.valueOf(time),
        p.x + sz / 2 - BFS / 3, p.y + sz / 2 + BFS / 3,
        assets.bombTextP);
  }

  static public void drawBrick(Canvas canvas, int[][] brick, Vect p, float scale) {
    float size = canvas.getWidth() * scale;
    float tSize = size / Game.GRID_S;

    for (int i = 0; i < brick.length; i++) {
      for (int j = 0; j < brick[i].length; j++) {
        Vect np = p.plus(tSize * i, tSize * j);

        if (brick[i][j] == 1)
          Drawer.drawBrickTile(canvas, np, tSize);
        else if (brick[i][j] >= 2)
          Drawer.drawBomb(canvas, np, tSize, 8 - brick[i][j]);

        if (scale == 1)
          Drawer.drawTile(canvas, np, tSize);
      }
    }
  }

  static public void drawBrickCenter(Canvas canvas, int[][] brick, Vect p, float scale) {
    float w = canvas.getWidth();
    float tileS = w / Game.GRID_S * scale;

    Vect d = new Vect(brick.length, brick[0].length).mult(- tileS / 2);
    drawBrick(canvas, brick, p.plus(d), scale);
  }


  static public void drawGrid(Canvas canvas, Grid grid) {
    drawBrick(canvas, grid.grid, new Vect(0, TOP_MARGIN), 1f);
  }


  static public void drawBar(Canvas canvas, BrickBar bar) {
    final float scale = 0.6f;

    float w = canvas.getWidth();
    float barS = w / Game.BAR_S;
    Vect p = new Vect(barS / 2, TOP_MARGIN + w + 200);

    for (int i = 0; i < Game.BAR_S; i++) {
      drawBrickCenter(canvas, bar.bricks[i], p.plusX(barS * i), scale);
    }
  }
}
