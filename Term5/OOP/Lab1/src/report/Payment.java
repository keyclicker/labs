package report;

public class Payment implements Comparable<Payment> {
  public enum Type {
    INCOME(38.5f),
    ROYALTY(30f),
    SALE(7.25f),
    GIFT(10.5f),
    ABROAD(20f),
    BENEFIT(15.4f);

    public final float rate;

    Type(float rate) {
      this.rate = rate;
    }
  }

  private final Type type;
  private final float amount;
  private final String name;

  public Payment(Type type, float amount, String name) {
    this.type = type;
    this.amount = amount;
    this.name = name;
  }

  public Type getType() {
    return type;
  }

  public float getAmount() {
    return amount;
  }

  public float getTax() {
    return amount * type.rate / 100.0f;
  }

  public String getName() {
    return name;
  }

  @Override
  public int compareTo(Payment p) {
    return Float.compare(this.getTax(), p.getTax());
  }

  @Override
  public String toString() {
    return String.format(Report.FORMAT,
        String.format("%.1f", getTax()),
        String.format("%.1f", getAmount()),
        String.format("%.1f", getType().rate),
        type.toString().toLowerCase(), getName());
  }

  public static Payment parse(String str) {
    var split = str.split(" ", 3);
    return new Payment(
        Type.valueOf(split[0].toUpperCase()),
        Float.parseFloat(split[1]),
        split[2]
    );
  }
}
