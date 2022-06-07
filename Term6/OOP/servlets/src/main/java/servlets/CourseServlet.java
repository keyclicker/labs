package servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import model.Course;
import model.User;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet(urlPatterns = {"/course"})
public class CourseServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=UTF-8");

        PrintWriter out = resp.getWriter();

        try {
            var user = User.fromCookies(req.getCookies());
            var json = Utils.getBody(req);
            var course = new Course(user,
                    json.getString("name"),
                    json.getString("description"));

            out.write("{\"id\": "
                    + course.insert() + " }");

        } catch (SQLException e) {
            resp.setStatus(400);
            out.write(e.toString());
        }
    }

    @Override
    protected void doDelete(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=UTF-8");

        PrintWriter out = resp.getWriter();

        try {
            var user = User.fromCookies(req.getCookies());
            var json = Utils.getBody(req);
            var course = new Course();
            course.setId(json.getInt("id"));
            course.delete(user.getUsername());
        } catch (Exception e) {
            resp.setStatus(400);
            out.write(e.toString());
        }
    }
}
