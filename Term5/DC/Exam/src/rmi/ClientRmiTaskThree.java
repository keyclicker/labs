package rmi;

import java.util.Scanner;
import java.rmi.Naming;


public class ClientRmiTaskThree {
  public static void main(String[] args) throws Exception {
    var choice = 1000;
    int a, b;

    var in = new Scanner(System.in);

    try {
      RMI st = (RMI) Naming.lookup("//localhost:5000/hospital");
      System.out.println("Choose option:\n"
          + "1 - alphabetic order\n"
          + "2 - medical id in interval of A and B\n");

      choice = in.nextInt();

      switch (choice) {
        case 1:
          System.out.println(st.displayAlphabetic());
          break;
        case 2:
          System.out.print("Enter A value: ");
          a = in.nextInt();

          System.out.print("Enter B value: ");
          b = in.nextInt();

          System.out.println(st.displayInterval(a, b));
          break;
      }
    } catch (Exception e) { e.printStackTrace(); }
  }
}