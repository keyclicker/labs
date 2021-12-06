package parsers;

import poscard.Album;
import poscard.Postcard;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;

public class DOM {
  private static String getAtr(Element e, String key) {
    return e.getAttribute(key);
  }

  private static String getElem(Element e, String key) {
    return e.getElementsByTagName(key).item(0).getTextContent();
  }

  public static Album parse(String xmlPath, String xsdPath) {
    try {
      Validator.validate(xmlPath, xsdPath);
      var album = new Album();

      var builderFactory = DocumentBuilderFactory.newInstance();
      var builder = builderFactory.newDocumentBuilder();
      var document = builder.parse(new File(xmlPath));

      var planeNodes = document.getDocumentElement().getChildNodes();

      for (int i = 0; i < planeNodes.getLength(); ++i) {
        Node node = planeNodes.item(i);
        if (node instanceof Element e) {
          album.add(new Postcard(
              getAtr(e, "id"),
              getAtr(e, "sent"),
              getElem(e, "theme"),
              getElem(e, "type"),
              getElem(e, "year"),
              getElem(e, "country"),
              getElem(e, "author"),
              getElem(e, "value")
          ));
        }
      }

      return album;
    } catch (Exception e) {
      e.printStackTrace();
    }
    return null;
  }
}
