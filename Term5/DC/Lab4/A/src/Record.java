import java.util.concurrent.ThreadLocalRandom;

class Record {
  public String name, phoneNumber;

  Record() {}
  Record(String name, String phoneNumber) {
    this.name = name;
    this.phoneNumber = phoneNumber;
  }

  public static Record parse(String record) {
    var arr = record.split(":");
    if (arr.length == 2)
      return new Record(arr[0].trim(), arr[1].trim());
    else
      return new Record();
  }

  @Override
  public String toString() {
    return name + " : " + phoneNumber;
  }

  // For random generation and for random search
  static private final String[] names = {
      "John", "Smith", "Jim", "Morrison", "Bob", "Dylan", "Michael",
      "Scott", "John", "Lennon", "Paul", "Thomas", "Anderson",
      "Lars", "Trier"
  };

  static public String randName() {
    return names[ThreadLocalRandom.current().nextInt(names.length)];
  }

  static public String randNumber() {
    var rand = ThreadLocalRandom.current();
    return String.format("%03d", rand.nextInt(1000)) + "-" +
        String.format("%03d", rand.nextInt(1000)) + "-" +
        String.format("%04d", rand.nextInt(10000));
  }

  static public String randNumberQuery() {
    var rand = ThreadLocalRandom.current();
    return String.format("%03d", rand.nextInt(1000));
  }

  static public Record randRecord() {
    return new Record(randName() + " " + randName(), randNumber());
  }
}
