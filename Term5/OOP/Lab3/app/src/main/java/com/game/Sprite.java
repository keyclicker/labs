package com.game;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Picture;
import android.view.TextureView;

public class Sprite extends Drawable {
  Color color;
  int xd, yd;

  Sprite(int x, int y, int xd, int yd, Paint color, Drawable parent) {
    super(x, y, parent);
    this.color = color;
    this.xd = xd;
    this.yd = yd;
  }

  @Override
  void onDraw(Canvas canvas) {
    canvas.drawRect(getAbsX(), getAbsY(), xd, yd, Paint.Style.);
  }
}