package servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import model.Session;
import model.User;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet(urlPatterns = {"/logout"})
public class LogoutServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=UTF-8");

        PrintWriter out = resp.getWriter();

        try {
            var user = User.fromCookies(req.getCookies());
            var session = new Session(user.getValue());
            session.delete();
            out.write("{\"status\":\"ok\"}");
        } catch (Exception e) {
            resp.setStatus(400);
            out.write(e.toString());
        }
    }
}
