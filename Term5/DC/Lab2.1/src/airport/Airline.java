package airport;

import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import javax.xml.XMLConstants;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import java.io.File;
import java.util.HashMap;

public class Airline {
  Airport airport;
  HashMap<Integer, Flight> flights = new HashMap<>();
  Element element;

  private int id;
  private String name;
  private String city; //Headquarter City

  Airline(Airport airport, Element element) {
    this.airport = airport;
    this.element = element;
    this.id = Integer.parseInt(element.getAttribute("id"));
    this.name = element.getAttribute("name");
    this.city = element.getAttribute("city");

    airport.airlines.put(id, this);

    var flightNodes = element.getElementsByTagName("Flight");
    for (int i = 0; i < flightNodes.getLength(); i++) {
      var flightN = (Element) flightNodes.item(i);
      new Flight(this, flightN);
    }
  }

  public void putFlight(Integer key, Flight value) {
    flights.put(key, value);
    airport.flights.put(key, value);
  }

  public String toString() {
    var sb = new StringBuilder();
    sb.append(String.format("%d: name=\"%s\" city=\"%s\"\n", id, name, city));
    for (var a: flights.values()) {
      sb.append(a);
    }
    sb.append("\n");
    return sb.toString();
  }

  public int getId() {
    return id;
  }

  public void setId(int id) {
    this.id = id;
    element.setAttribute("id", String.valueOf(id));
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
    element.setAttribute("name", String.valueOf(name));
  }

  public String getCity() {
    return city;
  }

  public void setCity(String city) {
    this.city = city;
    element.setAttribute("city", String.valueOf(city));
  }
}
