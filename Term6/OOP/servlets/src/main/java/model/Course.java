package model;

import lombok.Getter;
import lombok.Setter;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class Course {
    @Getter @Setter
    private int id;
    @Getter @Setter
    private User professor;
    @Getter @Setter
    private String name;
    @Getter @Setter
    private String description;
    @Getter @Setter
    private ArrayList<User> students;

    public Course(int id, User professor, String name, String description) {
        this.id = id;
        this.professor = professor;
        this.name = name;
        this.description = description;
        this.students = new ArrayList<User>();
    }

    static public ArrayList<Course> search(String query) throws SQLException {
        // language=SQL
        query = query.toLowerCase();
        String s = "SELECT course_id, username, name, type, course_name, description " +
                "FROM courses JOIN users " +
                "ON courses.professor_username = users.username " +
                "WHERE LOWER(course_name) LIKE '%" + query + "%' " +
                "OR LOWER(description) LIKE '%" + query + "%'" +
                "OR LOWER(name) LIKE '%" + query + "%'";

        ResultSet rs = Database.Request(s);

        ArrayList<Course> courses = new ArrayList<Course>();
        while (rs.next()) {
            int id = rs.getInt("course_id");
            String username = rs.getString("username");
            String name = rs.getString("name");
            int type = rs.getInt("type");
            String courseName = rs.getString("course_name");
            String description = rs.getString("description");
            Course course = new Course(id,
                    new User(username, name, type), courseName, description);
            courses.add(course);
        }
        return courses;
    }

}

