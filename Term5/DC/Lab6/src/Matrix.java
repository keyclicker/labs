import java.awt.*;
import java.util.Vector;
import java.util.concurrent.ThreadLocalRandom;

public class Matrix {
  private final Vector<Vector<Float>> matrix;

  Matrix(int m, int n) {
    matrix = new Vector<>(m);
    for (int i = 0; i < m; i++) {
      matrix.add(new Vector<>(n));
      for (int j = 0; j < n; j++) {
        // for demo
        matrix.get(i).add(ThreadLocalRandom.current().nextFloat() * 100.0F);
        //matrix.get(i).add(0.0F);
      }
    }
  }

  public float get(int i, int j) {
    return matrix.get(i).get(j);
  }

  public void set(int i, int j, float value) {
    matrix.get(i).set(j, value);
  }

  public void setRow(int i, Vector<Float> line) {
    matrix.set(i, line);
  }

  public int height() {
    return matrix.size();
  }

  public int width() {
    return matrix.firstElement().size();
  }

  @Override
  public String toString() {
    var sb = new StringBuilder();
    for (int i = 0; i < height(); i++) {
      sb.append("| ");
      for (int j = 0; j < width(); j++) {
        sb.append(String.format(" %4.1f ", get(i, j)));
      }
      sb.append(" |\n");
    }
    return sb.toString();
  }
}