package report;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import report.Payment;

class PaymentTest {
  private final Payment.Type TYPE = Payment.Type.INCOME;
  private final float AMOUNT = 50;
  private final String NAME = "Test";

  private final Payment payment =
      new Payment(TYPE, AMOUNT, NAME);

  @Test
  void compareTo() {
    var p = new Payment(Payment.Type.ABROAD, 80, "Test2");
    assertEquals(payment.compareTo(p),
        Float.compare(AMOUNT * TYPE.rate / 100.0f, p.getTax()));
  }

  @Test
  void parseAndToString() {
    var str = String.join(" ",
        TYPE.toString().toLowerCase(), String.valueOf(AMOUNT), NAME);

    var p = Payment.parse(str);
    assertEquals(p.getType(), payment.getType());
    assertEquals(p.getAmount(), payment.getAmount());
    assertEquals(p.getName(), payment.getName());

    assertEquals(p.toString(), payment.toString());
  }
}