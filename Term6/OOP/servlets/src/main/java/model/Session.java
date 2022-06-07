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

    public Session(String value) {
        this.value = value;
    }

    public Session(String username, String value) {
        this.username = username;
        this.value = value;
    }

    public static Session createNew(String username) throws SQLException {
        Session session = new Session(username, "");
        session.username = username;
        session.date = OffsetDateTime.now();

        SecureRandom random = new SecureRandom();
        byte[] values = new byte[32];
        random.nextBytes(values);

        session.value = DigestUtils.sha256Hex(values);
        return session;
    }

    public void insert() throws SQLException {
        // language=SQL
        String s = "INSERT INTO sessions (username, date, value) " +
                "VALUES ('" + username + "', '" + date.toString() + "', '"
                + value + "') RETURNING session_id";
        Database.Request(s);
    }

    public void delete() throws SQLException {
        // language=SQL
        String s = "DELETE FROM sessions WHERE value = '" + value +"' RETURNING session_id";
        Database.Request(s);
    }
}
