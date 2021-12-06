import parsers.DOM;
import parsers.SAX;
import parsers.StAX;
import poscard.Album;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class Tests {
  Album albumDOM = DOM.parse("res/album.xml", "res/album.xsd");
  Album albumSAX = SAX.parse("res/album.xml", "res/album.xsd");
  Album albumStAX = StAX.parse("res/album.xml", "res/album.xsd");

  @Test
  public void toStringTest() {
    assertEquals(albumDOM.toString(), albumSAX.toString());
    assertEquals(albumSAX.toString(), albumStAX.toString());
  }

  @Test
  public void equals() {
    assertEquals(albumDOM, albumSAX);
    assertEquals(albumSAX, albumStAX);

    assertEquals(albumDOM.getPostcards().first(),
        albumSAX.getPostcards().first());

    assertEquals(albumSAX.getPostcards().first(),
        albumStAX.getPostcards().first());
  }

  @Test
  public void invalidTest() {
    assertNull(DOM.parse("res/invalidAlbum.xml", "res/album.xsd"));
    assertNull(SAX.parse("res/invalidAlbum.xml", "res/album.xsd"));
    assertNull(StAX.parse("res/invalidAlbum.xml", "res/album.xsd"));
  }
}
