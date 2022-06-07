package servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import model.Course;
import model.Database;
import model.User;

import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(urlPatterns = {"/rate"})
public class RateServlet extends HttpServlet {
    @Override
    protected void doPut(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=UTF-8");
        PrintWriter out = resp.getWriter();

        try {
            var json = Utils.getBody(req);
            //language=SQL
            String q = "UPDATE courses_students" +
                    " SET mark = " + json.getInt("mark") +
                    " WHERE course_id = " + json.getInt("course_id") +
                    " AND student_username = '" +
                    json.getString("student_username") +"'";

            Database.Request(q);

            out.write("{\"status\":\"ok\"}");
        } catch (Exception e) {
            resp.setStatus(400);
            out.write(e.toString());
        }
    }
}
