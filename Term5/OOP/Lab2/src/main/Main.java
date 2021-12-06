package main;

import parsers.DOM;
import parsers.SAX;
import parsers.StAX;

public class Main {
  public static void main(String[] args) {
    var albumDOM = DOM.parse("res/album.xml", "res/album.xsd");
    var albumSAX = SAX.parse("res/album.xml", "res/album.xsd");
    var albumStAX = StAX.parse("res/album.xml", "res/album.xsd");

    System.out.printf("DOM:\n%s\n", albumDOM);
    System.out.printf("SAX:\n%s\n", albumSAX);
    System.out.printf("StAX:\n%s\n", albumStAX);
  }
}
