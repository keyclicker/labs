package com.game;

import android.graphics.Canvas;

public class Grid extends Drawable {
  Canvas canvas;
  int xd, yd;


  Grid(int xd, int yd, Drawable parent) {
    super(parent);
    this.xd = xd;
    this.yd = yd;
  }

//  @Override
//  private void onDraw(Canvas canvas) {
//    super.onDraw(canvas);
//  }
}
