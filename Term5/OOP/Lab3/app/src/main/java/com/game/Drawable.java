package com.game;

import android.graphics.Canvas;
import android.graphics.Point;

import java.util.ArrayList;
import java.util.List;

public class Drawable {
  private final Drawable parent;
  private final ArrayList<Drawable> children = new ArrayList<>();
  private Point pos = new Point();

  Drawable(Drawable parent) {
    this.parent = parent;
  }

  Drawable(int x, int y, Drawable parent) {
    this.parent = parent;
    pos.set(x, y);
  }

  public void draw(Canvas canvas) {
    onDraw(canvas);
    for (Drawable c: children) {
      c.draw(canvas);
    }
  }

  void onDraw(Canvas canvas) {}

  public void setPos(int x, int y) {
    pos.set(x, y);
  }

  public void move(int dx, int dy) {
    pos.offset(dx, dy);
  }

  public Point getPos() {
    return new Point(pos.x, pos.y);
  }

  public Point getAbsPos() {
    int px = 0, py = 0;
    if (parent != null) {
      px = parent.getAbsPos().x;
      py = parent.getAbsPos().y;
    }
    return new Point(pos.x + px, pos.y + py);
  }

  public int getAbsX() {
    int px = 0;
    if (parent != null) px = parent.getAbsPos().x;
    return pos.x + px;
  }

  public int getAbsY() {
    int py = 0;
    if (parent != null) py = parent.getAbsPos().y;
    return pos.y + py;
  }
}
