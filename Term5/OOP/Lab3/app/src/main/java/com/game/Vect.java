package com.game;

import java.util.Objects;

public class Vect {
  public float x, y;

  Vect() {}

  public Vect(float x, float y) {
    this.x = x;
    this.y = y;
  }

  public Vect(Vect v) {
    this.x = v.x;
    this.y = v.y;
  }

  public void set(Vect v) {
    this.x = v.x;
    this.y = v.y;
  }
  public void set(float x, float y) {
    this.x = x;
    this.y = y;
  }
  public void set(float x) {
    this.x = x;
  }
  public void setY(float y) {
    this.y = y;
  }

  public Vect plus(Vect v) {
    return new Vect(this.x + v.x, this.y + v.y);
  }
  public Vect plus(float x, float y) {
    return new Vect(this.x + x, this.y + y);
  }
  public Vect plusX(float x) {
    return new Vect(this.x + x, this.y);
  }
  public Vect plusY(float y) {
    return new Vect(this.x, this.y + y);
  }

  public Vect mult(float l) {
    return new Vect(x * l, y * l);
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Vect vect = (Vect) o;
    return Float.compare(vect.x, x) == 0 && Float.compare(vect.y, y) == 0;
  }

  @Override
  public int hashCode() {
    return Objects.hash(x, y);
  }
}
