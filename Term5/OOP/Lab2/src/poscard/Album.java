package poscard;

import java.util.Objects;
import java.util.TreeSet;

public class Album {
  private final TreeSet<Postcard> postcards = new TreeSet<>();

  public void add(Postcard e) {
    postcards.add(e);
  }

  public TreeSet<Postcard> getPostcards() {
    return postcards;
  }

  @Override
  public String toString() {
    var sb = new StringBuilder();
    sb.append(String.format(Postcard.FORMAT, "ID", "Sent",
        "Theme", "Type", "Value", "Year", "Country", "Author"));

    for (var p: postcards) {
      sb.append(p);
    }
    return sb.toString();
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Album album = (Album) o;
    return Objects.equals(postcards, album.postcards);
  }
}
