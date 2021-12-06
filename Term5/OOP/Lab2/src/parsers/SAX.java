package parsers;

import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;
import poscard.Album;
import poscard.Postcard;

import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.util.Objects;

public class SAX {
  private static class ArticleHandler extends DefaultHandler {
    private Album album;
    private Postcard postcard;
    private StringBuilder sb;

    @Override
    public void characters(char[] ch, int start, int length) {
      sb.append(ch, start, length);
    }

    @Override
    public void startDocument() {
      album = new Album();
    }

    @Override
    public void startElement(String uri, String lName, String qName, Attributes attr) {
      sb = new StringBuilder();

      if (Objects.equals(qName, "postcard")) {
        postcard = new Postcard();
        postcard.setId(attr.getValue("id"));
        postcard.setSent(attr.getValue("sent"));
      }
    }

    @Override
    public void endElement(String uri, String lName, String qName) {
      var value = sb.toString().trim();

      switch (qName) {
        case "theme" -> postcard.setTheme(value);
        case "type" -> postcard.setType(value);
        case "value" -> postcard.setValue(value);
        case "country" -> postcard.setCountry(value);
        case "author" -> postcard.setAuthor(value);
        case "year" -> postcard.setYear(value);
        case "postcard" -> album.add(postcard);
      }
    }

    public Album getAlbum() {
      return album;
    }
  }

  public static Album parse(String xmlPath, String xsdPath) {
    try {
      Validator.validate(xmlPath, xsdPath);

      var factory = SAXParserFactory.newInstance();
      var parser = factory.newSAXParser();

      var ah = new ArticleHandler();
      parser.parse(new File(xmlPath), ah);

      return ah.getAlbum();
    } catch (Exception e) {
      e.printStackTrace();
    }
    return null;
  }
}
