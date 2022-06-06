package model;

import lombok.Getter;
import lombok.Setter;
import org.apache.commons.codec.digest.DigestUtils;

import java.security.SecureRandom;
import java.sql.SQLException;
import java.time.OffsetDateTime;

public class Session {
    @Getter @Setter
    private int sessionId;
    @Getter @Setter
    private String username;
    @Getter @Setter
    private OffsetDateTime date;
    @Getter @Setter
    private String value;

    public Session(String username) {
        this.username = username;
        this.date = OffsetDateTime.now();

        SecureRandom random = new SecureRandom();
        byte[] values = new byte[32];
        random.nextBytes(values);

        this.value = DigestUtils.sha256Hex(values);
    }

    public void save() throws SQLException {
        // language=SQL
        String s = "INSERT INTO sessions (username, date, value) " +
                "VALUES ('" + username + "', '" + date.toString() + "', '"
                + value + "') RETURNING session_id";
        Database.Request(s);
    }
}
