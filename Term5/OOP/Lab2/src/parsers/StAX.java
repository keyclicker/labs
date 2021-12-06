package parsers;

import poscard.Album;
import poscard.Postcard;

import javax.xml.namespace.QName;
import javax.xml.stream.XMLInputFactory;
import java.io.FileInputStream;

public class StAX {
  public static Album parse(String xmlPath, String xsdPath) {
    try {
      Validator.validate(xmlPath, xsdPath);

      var xmlInputFactory = XMLInputFactory.newInstance();
      var reader = xmlInputFactory.
          createXMLEventReader(new FileInputStream(xmlPath));

      var album = new Album();
      Postcard postcard = new Postcard();

      while (reader.hasNext()) {
        var event = reader.nextEvent();

        if (event.isStartElement()) {
          var startElement = event.asStartElement();
          var tag = startElement.getName().getLocalPart();

          if (tag.equals("postcard")) {
            postcard = new Postcard();
            postcard.setId(startElement.
                getAttributeByName(new QName("id")).getValue());
            postcard.setSent(startElement.
                getAttributeByName(new QName("sent")).getValue());

          } else {
            event = reader.nextEvent();
            var value = event.asCharacters().getData();

            switch (tag) {
              case "theme" -> postcard.setTheme(value);
              case "type" -> postcard.setType(value);
              case "value" -> postcard.setValue(value);
              case "country" -> postcard.setCountry(value);
              case "author" -> postcard.setAuthor(value);
              case "year" -> postcard.setYear(value);
            }
          }
        }

        if (event.isEndElement()) {
          var endElement = event.asEndElement();
          if (endElement.getName().getLocalPart().equals("postcard")) {
            album.add(postcard);
          }
        }
      }

      return album;
    } catch (Exception e) {
      e.printStackTrace();
    }
    return null;
  }
}
