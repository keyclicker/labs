package model;

import lombok.Getter;
import lombok.Setter;
import org.apache.commons.codec.digest.DigestUtils;

import java.sql.ResultSet;
import java.sql.SQLException;

public class User {
    @Getter @Setter
    private String username;
    @Getter @Setter
    private String name;
    @Getter @Setter
    private int type;

    @Getter @Setter
    private String password;

    @Getter @Setter
    private String pwdHash;

    public User(String username, String name, int type, String password) {
        this.username = username;
        this.name = name;
        this.type = type;
        this.password = password;
    }

    public User(String username, String name, int type) {
        this.username = username;
        this.name = name;
        this.type = type;
    }

    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public void signup() throws SQLException {
        pwdHash = DigestUtils.sha256Hex(
                password + username + "udex.courses");

        // language=SQL
        String s = "INSERT INTO users (username, name, type, pwd_hash) " +
                "VALUES ('" + username + "', '" + name + "', "
                + type + ", '" + pwdHash + "') RETURNING username";

        Database.Request(s);
    }

    public boolean signin() throws SQLException {
        pwdHash = DigestUtils.sha256Hex(
                password + username + "udex.courses");

        // language=SQL
        String s = "SELECT * FROM users " +
                "WHERE username = '" + username + "' " +
                "AND pwd_hash = '" + pwdHash + "'";

        ResultSet rs = Database.Request(s);
        return rs.next();
    }

    static public User getUser(String value) throws SQLException {
        // language=SQL
        String s = "SELECT users.username, name, type FROM users " +
                "JOIN sessions ON sessions.username = users.username " +
                "WHERE value = '" + value + "'";

        var rs = Database.Request(s);
        if (rs.next()) {
            var username = rs.getString("username");
            var name = rs.getString("name");
            var type = rs.getInt("type");
            return new User(username, name, type);
        }

        return null;
    }
}
