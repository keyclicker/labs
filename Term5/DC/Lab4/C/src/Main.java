import java.util.concurrent.ThreadLocalRandom;

public class Main {
  static final int sleep = 500;
  static ThreadLocalRandom rand = ThreadLocalRandom.current();

  static String genName() {
    final String[] cityNames = {
        "los", "angeles", "santa", "monica", "san", "kiev",
        "chernivtsi", "nizhyn", "burg", "grad", "ivka" };
    var size = cityNames.length;
    var sep = rand.nextInt(3) == 0 ? " " : "";
    return cityNames[rand.nextInt(size)] + sep + cityNames[rand.nextInt(size)];
  }

  static void priceChanger() {
    while (!Thread.interrupted()) {
      lock.writeLock();

      var a = rotes.getRandomCity();
      var b = rotes.getRandomCity();

      var route = rotes.getRote(a, b);
      var prevPrice = route == null ? null : route.price;
      var newPrice = rand.nextFloat() * 1000;

      System.out.println("edit: " + a + " -> " + b + ": " + prevPrice + " -> " + newPrice);
      rotes.addRoute(a, b, new BusRoutes.Route(newPrice));

      lock.writeUnlock();
      try { Thread.sleep(sleep); }
      catch (InterruptedException e) {e.printStackTrace();}
    }
  }

  static void routeAddRem() {
    while (!Thread.interrupted()) {
      lock.writeLock();

      var a = rotes.getRandomCity();
      var b = rotes.getRandomCity();

      var action = rand.nextInt(3);

      if (action == 0) {
        rotes.removeRoute(a, b);
        System.out.println("remr: " + a + " -> " + b);
      } else {
        var price =  rand.nextFloat() * 1000;
        rotes.addRoute(a, b, new BusRoutes.Route(price));
        System.out.println("addr: " + a + " -> " + b + ": " + price);
      }

      lock.writeUnlock();
      try { Thread.sleep(sleep); }
      catch (InterruptedException e) {e.printStackTrace();}
    }
  }

  static void cityAddRem() {
    while (!Thread.interrupted()) {
      lock.writeLock();

      var action = rand.nextInt(3);

      if (action == 0) {
        var city = rotes.getRandomCity();
        rotes.removeCity(rotes.getRandomCity());
        System.out.println("remc: " + city);
      } else {
        var name = genName();
        rotes.addCity(new BusRoutes.City(name));
        System.out.println("addc: " + name);
      }

      lock.writeUnlock();
      try { Thread.sleep(sleep); }
      catch (InterruptedException e) {e.printStackTrace();}
    }
  }


  static void priceGetter() {
    while (!Thread.interrupted()) {
      lock.readLock();

      var a = rotes.getRandomCity();
      var b = rotes.getRandomCity();
      System.out.println("calc: " + a + " -> " + b + ": " + rotes.calcRoutePrice(a, b));;

      lock.readUnlock();
      try { Thread.sleep(sleep); }
      catch (InterruptedException e) {e.printStackTrace();}
    }
  }


  static BusRoutes rotes = new BusRoutes();
  static RWLock lock = new RWLock();

  public static void main(String[] args) {
    for (int i = 0; i < 5; i++) {
      rotes.addCity(new BusRoutes.City(genName()));
    }
    for (int i = 0; i < 10; i++) {
      rotes.addRoute(rotes.getRandomCity(), rotes.getRandomCity(),
          new BusRoutes.Route(rand.nextFloat()*1000));
    }

    new Thread(Main::priceChanger).start();
    new Thread(Main::routeAddRem).start();
    new Thread(Main::cityAddRem).start();
    new Thread(Main::priceGetter).start();
  }
}
