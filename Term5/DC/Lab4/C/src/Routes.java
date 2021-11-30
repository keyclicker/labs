import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

public class Routes {
  static class City {
    String name;
    City(String name) {
      this.name = name;
    }
    public String toString() {
      return name;
    }
  }

  static class Route {
    float price;
    Route(float price) {
      this.price = price;
    }
    Route(Route route) {
      this.price = route.price;
    }
  }

  private final HashMap<City, HashMap<City, Route>> routes;

  Routes() {
    routes = new HashMap<>();
  }

  public void addRoute(City a, City b, Route route) {
    routes.get(a).put(b, route);
    routes.get(b).put(a, route);
  }

  public void removeRoute(City a, City b) {
    routes.get(a).remove(b);
    routes.get(b).remove(a);
  }

  public void addCity(City city) {
    routes.put(city, new HashMap<>());
  }

  public void removeCity(City city) {
    routes.remove(city);
  }

  public Route getRote(City a, City b) {
    return routes.get(a).get(b);
  }

  public City getRandomCity() {
    if (routes.isEmpty()) return null;
    return new ArrayList<City>(routes.keySet()).get(
        ThreadLocalRandom.current().nextInt(routes.size()));
  }

  private float dfs(City a, City b, HashSet<City> visited, float price) {
    for (var city : routes.get(a).keySet()) {
      price += routes.get(a).get(city).price;
      if (city == b)
        return price;
      else
        if (!visited.contains(city)) {
          visited.add(city);
          return dfs(a, b, visited, price);
        }
    }
    return Float.POSITIVE_INFINITY;
  }

  public float calcRoutePrice(City a, City b) {
    var visited = new HashSet<City>();
    return dfs(a, b, visited, 0);
  }

}
