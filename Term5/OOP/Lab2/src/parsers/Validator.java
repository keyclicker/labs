package parsers;

import org.xml.sax.SAXException;

import javax.xml.XMLConstants;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.SchemaFactory;
import java.io.FileInputStream;
import java.io.IOException;

public class Validator {
  public static void validate(String xmlPath, String xsdPath) throws Exception {
    var xmlStream = new FileInputStream(xmlPath);
    var xsdStream = new FileInputStream(xsdPath);

    var factory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
    var schema = factory.newSchema(new StreamSource(xsdStream));
    var validator = schema.newValidator();

    validator.validate(new StreamSource(xmlStream));
  }
}
