package report;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Report {
  protected final ArrayList<Payment> payments = new ArrayList<>();
  protected float totalTax, totalAmount;

  public Report(String file) throws FileNotFoundException {
    var scanner = new Scanner(new File(file));

    while (scanner.hasNextLine()) {
      var line = scanner.nextLine();
      if (!line.startsWith("//") &&
          line.split(" ", 3).length == 3) {
        var payment = Payment.parse(line);
        payments.add(payment);
        totalTax += payment.getTax();
        totalAmount += payment.getAmount();
      }
      Collections.sort(payments);
    }
  }

  static final protected String FORMAT = "%10s %10s %8s %10s   %s\n";

  @Override
  public String toString() {
    var sb = new StringBuilder();
    sb.append(String.format(FORMAT,
        "Tax", "Amount", "Rate", "Type", "Description"));

    for (var p : payments) {
      sb.append(p.toString());
    }

    sb.append(String.format("\n%10.1f %10.1f %8.1f - Summary",
        totalTax, totalAmount, totalTax / totalAmount * 100.0f));
    return sb.toString();
  }
}
