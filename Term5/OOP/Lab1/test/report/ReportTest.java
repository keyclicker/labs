package report;

import org.junit.jupiter.api.Test;

import java.io.FileNotFoundException;

import static org.junit.jupiter.api.Assertions.*;

class ReportTest {
  Report report;

  ReportTest() throws FileNotFoundException {
    report = new Report("taxes.txt");
  }

  @Test
  void totalTest() {
    float totalTax = 0, totalAmount = 0;
    for (var a : report.payments) {
      totalTax += a.getTax();
      totalAmount += a.getAmount();
    }
    assertEquals(totalAmount, report.totalAmount);
    assertEquals(totalTax, report.totalTax);
  }
}