import java.util.concurrent.ThreadLocalRandom;

public class Rookie {
  public enum Dir {
    Left, Right
  }

  static Dir randomDir() {
    if (ThreadLocalRandom.current().nextInt(2) == 0)
      return Dir.Left;
    else
      return Dir.Right;
  }

  private boolean decisionToRotate;
  private Dir dir = randomDir();

  public Rookie left, right;

  Rookie() {}

  Rookie(Rookie left, Rookie right) {
    this.left = left;
    this.right = right;
    if (left != null)
      left.right = this;
    if (right != null)
      right.left = this;
  }

  public void rotate() {
    if (dir == Dir.Left) dir = Dir.Right;
    else dir = Dir.Left;
  }

  public String toString() {
    return dir == Dir.Left ? " <" : " >";
  }

  public boolean makeDecision() {
    decisionToRotate =
        (dir == Dir.Right && right != null && right.dir == Dir.Left) ||
            (dir == Dir.Left && left != null && left.dir == Dir.Right);
    return decisionToRotate;
  }

  public void performDecision() {
    if (decisionToRotate) rotate();
  }
}