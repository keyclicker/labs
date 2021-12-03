public class Main {
  public static void main(String[] args) throws Exception {
    var a = new Matrix(2, 3);
    var b = new Matrix(3, 2);

    System.out.println(a);
    System.out.println(b);

    System.out.println(Multiply.sequential(a, b));
    System.out.println(Multiply.tape(a, b));

  }
}
