package com.game;

import android.content.Context;
import android.graphics.Canvas;
import android.view.View;

class Game extends View {
  Grid grid = new Grid(40, 40, null);

  public Game(Context context) {
    super(context);
  }

  @Override
  protected void onDraw(Canvas canvas) {
    grid.draw(canvas);
  }

}