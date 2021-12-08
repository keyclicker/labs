package airport;

import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

public class ParsingErrorHandler implements ErrorHandler {
  @Override
  public void warning(SAXParseException e) throws SAXException {
    System.out.println("Line " + e.getLineNumber() + ":");
    System.out.println(e.getMessage() + "\n");
  }

  @Override
  public void error(SAXParseException e) throws SAXException {
    System.out.println("Line " + e.getLineNumber() + ":");
    System.out.println(e.getMessage() + "\n");
  }

  @Override
  public void fatalError(SAXParseException e) throws SAXException {
    System.out.println("Line " + e.getLineNumber() + ":");
    System.out.println(e.getMessage() + "\n");
  }
}