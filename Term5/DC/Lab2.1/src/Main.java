/*
* Loading from file
* Saving in file
* new object
* editing object
* deleting object
* search
* */

import airport.Airport;

public class Main {
  public static void main(String[] args) throws Exception {
    var a = new Airport("res/airport.xml", "res/airport.xsd");

    System.out.println(a);

    a.addAirline(404, "NEW AIRLINE!!", "NO CITY!!!");
    a.addFlight(206, "Kyiv", "San Francisco", 404);
    a.editAirline(2, "EDITED!", "CITY");
    a.editFlight(7, "EDITED!", "EDITED TOO");
    a.deleteAirline(3);
    a.deleteFlight(8);

    System.out.println(a);
    a.saveToFile("res/saved.xml");


    var newA = new Airport();
    newA.addAirline(404, "NEW AIRLINE!!", "NO CITY!!!");
    newA.addFlight(206, "Kyiv", "San Francisco", 404);
    newA.editAirline(404, "EDITED!", "CITY");
    newA.editFlight(206, "EDITED!", "EDITED TOO");
    newA.saveToFile("res/new.xml");
  }
}
