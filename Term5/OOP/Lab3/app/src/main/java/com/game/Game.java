package com.game;

import android.content.Context;
import android.graphics.Canvas;
import android.view.MotionEvent;
import android.view.View;

class Game extends View {
  static final int GRID_S = 28;
  static final int BAR_S = 3;

  Grid grid = new Grid(GRID_S);
  BrickBar bar = new BrickBar(BAR_S);
  int[][] selBrick = null;
  int selIndex = -1;
  Vect p = new Vect();

  public Game(Context context) {
    super(context);
    Drawer.assets = new Drawer.Assets(context.getResources());
  }

  @Override
  protected void onDraw(Canvas canvas) {
    Drawer.drawGrid(canvas, grid);
    Drawer.drawBar(canvas, bar);

    if (selBrick != null) {
      Drawer.drawBrickCenter(canvas, selBrick, p, 1f);
    }
    invalidate();
  }


  @Override
  public boolean onTouchEvent(MotionEvent event) {
    if (event.getAction() == MotionEvent.ACTION_DOWN &&
        event.getY() > this.getWidth() + Drawer.TOP_MARGIN) {
      selIndex = (int) (event.getX() / this.getWidth() * BAR_S);
      selBrick = bar.get(selIndex);
      p.set(event.getX(), event.getY());
    }
    else if (event.getAction() == MotionEvent.ACTION_MOVE) {
      p.set(event.getX(), event.getY());
    }
    else if (event.getAction() == MotionEvent.ACTION_UP && selBrick != null) {
      Vect pa = p.plusY(- Drawer.TOP_MARGIN).mult((float) GRID_S / getWidth()).
          plus(-0.5f * selBrick.length, -0.5f * selBrick[0].length);

      if (grid.put(selBrick, Math.round(pa.x), Math.round(pa.y)))
        bar.remove(selIndex);

      selBrick = null;
      selIndex = -1;
    }
    return true;
  }
}