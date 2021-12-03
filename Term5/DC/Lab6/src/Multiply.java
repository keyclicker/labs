import java.util.ArrayList;
import java.util.Vector;
import java.util.concurrent.CyclicBarrier;

public class Multiply {
  private static final int THREAD_COUNT = Runtime.getRuntime().availableProcessors();

  static class Interval {
    int begin, end;
  }

  static private Interval getInterval(int taskCount, int threadNumber) {
    var in = new Interval();
    in.begin = threadNumber * (taskCount / THREAD_COUNT);
    if (threadNumber != THREAD_COUNT - 1)
      in.end = (threadNumber + 1) * (taskCount / THREAD_COUNT);
    else
      in.end = taskCount;

    return in;
  }
  
  static private float calcCell(Matrix a, Matrix b, int i, int j) {
    var res = 0;
    for (int k = 0; k < a.width(); k++) {
      res += a.get(i, k) * b.get(k, j);
    }
    return res;
  }

  static private Vector<Float> calcRow(Matrix a, Matrix b, int i) {
    var cr = new Vector<Float>(b.width());
    for (int j = 0; j < b.width(); j++) {
      cr.add(calcCell(a, b, i, j));
    }
    return cr;
  }

  static public Matrix sequential(Matrix a, Matrix b) throws Exception {
    if (a.width() != b.height())
      throw new Exception();

    var c = new Matrix(a.height(), b.width());
    for (int i = 0; i < a.height(); i++) {
      c.setRow(i, calcRow(a, b, i));
    }
    return c;
  }

  static public Matrix tape(Matrix a, Matrix b) throws Exception {
    if (a.width() != b.height())
      throw new Exception();

    var c = new Matrix(a.height(), b.width());
    var threads = new ArrayList<Thread>(THREAD_COUNT);

    for (int tn = 0; tn < THREAD_COUNT; tn++) {
      var in = getInterval(a.height(), tn);

      var thr = new Thread(() -> {
        for (int i = in.begin; i < in.end; i++) {
          c.setRow(i, calcRow(a, b, i));
        }
      });

      thr.start();
      threads.add(thr);
    }

    for (var thr: threads)
      thr.join();

    return c;
  }

  static public Matrix fox(Matrix a, Matrix b) throws Exception {
    if (a.width() != b.height())
      throw new Exception();

    var c = new Matrix(a.height(), b.width());
    var threads = new ArrayList<Thread>(THREAD_COUNT);

    for (int tn = 0; tn < THREAD_COUNT; tn++) {
      var in = getInterval(a.height(), tn);

      var thr = new Thread(() -> {
        for (int i = in.begin; i < in.end; i++) {
          c.setRow(i, calcRow(a, b, i));
        }
      });

      thr.start();
      threads.add(thr);
    }

    for (var thr: threads)
      thr.join();

    return c;
  }
}
