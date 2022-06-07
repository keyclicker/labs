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

    public Course() {}

    public Course(User professor, String name, String description) {
        this.professor = professor;
        this.name = name;
        this.description = description;
        this.students = new ArrayList<>();
    }

    public Course(int id, User professor, String name, String description) {
        this.id = id;
        this.professor = professor;
        this.name = name;
        this.description = description;
        this.students = new ArrayList<User>();
    }

    static public ArrayList<Course> search(String query) throws SQLException {
        query = "'%" + query + "%'";
        // language=SQL
        String s = "SELECT course_id, username, name, type, course_name, description " +
                "FROM courses JOIN users " +
                "ON courses.professor_username = users.username " +
                "WHERE course_name ILIKE " + query  +
                " OR description ILIKE " + query +
                " OR name ILIKE " + query +
                " ORDER BY course_id DESC";

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
            course.getStudents();
            courses.add(course);
        }
        return courses;
    }

    public int insert() throws SQLException {
        // language=SQL
        String s = "INSERT INTO courses (professor_username, course_name, description) " +
                "VALUES ('" + professor.getUsername() + "', '" + name + "', '" + description + "') " +
                "RETURNING course_id";

        return Database.Request(s).getInt("course_id");
    }

    public void delete(String username) throws SQLException {
        // language=SQL
        String s = "DELETE FROM courses WHERE course_id = " + id +
                " AND professor_username = '" + username + "' " +
                "RETURNING course_id";
        Database.Request(s);
    }

    public void enroll(User student) throws SQLException {
        // language=SQL
        String s = "INSERT INTO courses_students (course_id, student_username) " +
                "VALUES (" + id + ", '" + student.getUsername() + "') " +
                "RETURNING course_id";
        Database.Request(s);
    }

    public void unenroll(User student) throws SQLException {
        // language=SQL
        String s = "DELETE FROM courses_students WHERE course_id = " + id +
                " AND student_username = '" + student.getUsername() + "' " +
                "RETURNING course_id";
        Database.Request(s);
    }

    public ArrayList<User> getStudents() throws SQLException {
        // language=SQL
        String s = "SELECT username, name, type, mark FROM users " +
                "JOIN courses_students " +
                "ON users.username = courses_students.student_username " +
                "WHERE course_id = " + id;
        ResultSet rs = Database.Request(s);
        ArrayList<User> students = new ArrayList<User>();
        while (rs.next()) {
            var stud = new User();
            stud.setUsername(rs.getString("username"));
            stud.setName(rs.getString("name"));
            stud.setType(rs.getInt("type"));
            stud.setMark(rs.getInt("mark"));
            students.add(stud);
        }
        return students;
    }
}

