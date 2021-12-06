package poscard;

import java.time.Year;
import java.util.Objects;

public class Postcard implements Comparable<Postcard> {
  public enum Theme {
    CITY,
    LANDSCAPE,
    PEOPLE,
    RELIGION,
    SPORT,
    ARCHITECTURE
  }

  public enum Type {
    CONGRATS,
    COMMERCIAL,
    COMMON
  }

  public enum Value {
    HISTORICAL,
    COLLECTIBLE,
    THEMATIC
  }

  private int id;
  private boolean sent;
  private Theme theme;
  private Type type;
  private Year year;
  private String country;
  private String author;
  private Value value;

  public Postcard() {}
  
  public Postcard(String id, String sent, String theme, String type,
                  String year, String country, String author, String value) {
    setId(id);
    setSent(sent);
    setTheme(theme);
    setType(type);
    setYear(year);
    setCountry(country);
    setAuthor(author);
    setValue(value);
  }

  protected static final String FORMAT =
      "%5s %10s %10s %15s %15s %7s %20s %20s\n";

  @Override
  public String toString() {
    return String.format(FORMAT,
        id, sent, theme, type, value, year, country, author);
  }

  public int getId() {
    return id;
  }

  public void setId(String id) {
    this.id = Integer.parseInt(id);
  }

  public boolean isSent() {
    return sent;
  }

  public void setSent(String sent) {
    this.sent = Boolean.parseBoolean(sent);
  }

  public Theme getTheme() {
    return theme;
  }

  public void setTheme(String theme) {
    this.theme = Theme.valueOf(theme);
  }

  public Type getType() {
    return type;
  }

  public void setType(String type) {
    this.type = Type.valueOf(type);
  }

  public Year getYear() {
    return year;
  }

  public void setYear(String year) {
    this.year = Year.parse(year);
  }

  public String getCountry() {
    return country;
  }

  public void setCountry(String country) {
    this.country = country;
  }

  public String getAuthor() {
    return author;
  }

  public void setAuthor(String author) {
    this.author = author;
  }

  public Value getValue() {
    return value;
  }

  public void setValue(String value) {
    this.value = Value.valueOf(value);
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Postcard postcard = (Postcard) o;
    return getId() == postcard.getId() &&
        isSent() == postcard.isSent() &&
        getTheme() == postcard.getTheme() &&
        getType() == postcard.getType() &&
        Objects.equals(getYear(), postcard.getYear()) &&
        Objects.equals(getCountry(), postcard.getCountry()) &&
        Objects.equals(getAuthor(), postcard.getAuthor()) &&
        getValue() == postcard.getValue();
  }

  @Override
  public int compareTo(Postcard o) {
    return Integer.compare(this.id, o.id);
  }
}
