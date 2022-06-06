package model;

import lombok.Getter;
import lombok.Setter;

public class User {
    @Getter @Setter
    private String username;
    @Getter @Setter
    private String name;
    @Getter @Setter
    private int type;

    public User(String username, String name, int type) {
        this.username = username;
        this.name = name;
        this.type = type;
    }
}
