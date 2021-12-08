package airport;

import org.w3c.dom.Element;

public class Flight {
  Airline airline;
  Element element;

  private int id;
  private String from;
  private String to;

  Flight(Airline airline, Element element) {
    this.airline = airline;
    this.element = element;
    this.id = Integer.parseInt(element.getAttribute("id"));
    this.from = element.getAttribute("from");
    this.to = element.getAttribute("to");

    airline.putFlight(id, this);
  }

  public String toString() {
    return String.format("\t%d: from=\"%s\" to=\"%s\"\n", id, from, to);
  }

  public int getId() {
    return id;
  }

  public void setId(int id) {
    this.id = id;
    element.setAttribute("id", String.valueOf(id));
  }

  public String getFrom() {
    return from;
  }

  public void setFrom(String from) {
    this.from = from;
    element.setAttribute("from", from);
  }

  public String getTo() {
    return to;
  }

  public void setTo(String to) {
    this.to = to;
    element.setAttribute("to", to);
  }
}
