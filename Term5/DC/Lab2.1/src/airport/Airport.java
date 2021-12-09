package airport;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import java.io.File;
import java.util.HashMap;

public class Airport {
  DocumentBuilderFactory factory =  DocumentBuilderFactory.newInstance();

  HashMap<Integer, Airline> airlines = new HashMap<>();
  HashMap<Integer, Flight> flights = new HashMap<>();

  private DocumentBuilder builder;
  protected Document document;
  protected Element root;

  public Airport() throws Exception {
    builder = factory.newDocumentBuilder();
    document = builder.newDocument();
    root = document.createElement("Airport");
    document.appendChild(root);
  }
  public Airport(String path, String xsdPath) throws Exception {
    loadFromFile(path, xsdPath);
  }

  public void loadFromFile(String path, String xsdPath) throws Exception {
    SchemaFactory sf =
        SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
    Schema s = sf.newSchema(new File(xsdPath));
    factory.setSchema(s);

    builder = factory.newDocumentBuilder();
    builder.setErrorHandler(new ParsingErrorHandler());

    document = builder.parse(new File(path));
    root = (Element) document.getElementsByTagName("Airport").item(0);

    var airlineNodes = document.getElementsByTagName("Airline");
    for (int i = 0; i < airlineNodes.getLength(); i++) {
      var airlineN = (Element) airlineNodes.item(i);
      new Airline(this, airlineN);
    }
  }

  public void saveToFile(String path) throws Exception {
    var domSource = new DOMSource(document);
    var fileResult = new StreamResult(new File(path));
    var factory = TransformerFactory.newInstance();
    var transformer = factory.newTransformer();
    transformer.setOutputProperty(OutputKeys.ENCODING,"UTF-8");
    transformer.setOutputProperty(OutputKeys.INDENT, "yes");
    transformer.transform(domSource, fileResult);
  }

  public String toString() {
    var sb = new StringBuilder();
    sb.append("Airport:\n");
    for (var a: airlines.values()) {
      sb.append(a);
    }
    return sb.toString();
  }

  public Airline getAirline(int id) throws Exception {
    var airline = airlines.get(id);
    if (airline == null) throw new Exception("No airline with id = " + id);
    return airline;
  }

  public Flight getFlight(int id) throws Exception {
    var flights = this.flights.get(id);
    if (flights == null) throw new Exception("No airline with id = " + id);
    return flights;
  }

  public int countAirlines() {
    return airlines.size();
  }

  public int countFlights() {
    return flights.size();
  }

  public void addAirline(int id, String name, String city) {
    var element = document.createElement("Airline");
    element.setAttribute("id", String.valueOf(id));
    root.appendChild(element);
    var airline = new Airline(this, element);
    airline.setId(id);
    airline.setName(name);
    airline.setCity(city);
  }

  public void addFlight(int id, String from, String to, int airlineId) throws Exception {
    var element = document.createElement("Flight");
    element.setAttribute("id", String.valueOf(id));
    var airline = getAirline(airlineId);
    airline.element.appendChild(element);
    var flight = new Flight(airline, element);
    flight.setId(id);
    flight.setFrom(from);
    flight.setTo(to);
  }

  public void editAirline(int id, String name, String city) throws Exception {
    var airline = getAirline(id);
    airline.setName(name);
    airline.setCity(city);
  }

  public void editFlight(int id, String from, String to) throws Exception {
    var flight = getFlight(id);
    flight.setId(id);
    flight.setFrom(from);
    flight.setTo(to);
  }

  public void deleteAirline(int id) throws Exception {
    root.removeChild(getAirline(id).element);
    for (var k: airlines.get(id).flights.keySet()) {
      flights.remove(k);
    }
    airlines.remove(id);
  }

  public void deleteFlight(int id) throws Exception {
    var flight = getFlight(id);
    flight.airline.element
        .removeChild(flight.element);
    flight.airline.flights.remove(id);
    flights.remove(id);
  }
}
