package servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import model.Session;
import model.User;
import org.apache.commons.codec.digest.DigestUtils;

import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(urlPatterns = {"/login"})
public class LoginServlet extends HttpServlet {
    // Check if the user is logged in
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=UTF-8");
        PrintWriter out = resp.getWriter();
        out.write("{\"status\":\"ok\"}");
    }

    // Signup
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            req.setCharacterEncoding("UTF-8");
            resp.setContentType("application/json; charset=UTF-8");
            var body = Utils.getBody(req);

            var user = new User(
                    body.getString("username"),
                    body.getString("name"),
                    body.getInt("type"),
                    body.getString("password"));

            user.signup();

            var session = new Session(user.getUsername());
            session.save();

            resp.addCookie(new Cookie("session_id", session.getValue()));

            var out = resp.getWriter();
            out.write("{\"status\":\"ok\"}");
        }
        catch (Exception e) {
            resp.setStatus(400);
            var out = resp.getWriter();
            out.write(e.toString());
        }
    }

    // Login
    @Override
    protected void doPut(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            req.setCharacterEncoding("UTF-8");
            resp.setContentType("application/json; charset=UTF-8");
            var body = Utils.getBody(req);

            var user = new User(
                    body.getString("username"),
                    body.getString("password"));

            if (user.signin()) {
                var session = new Session(user.getUsername());
                session.save();

                resp.addCookie(new Cookie("session_id", session.getValue()));

                var out = resp.getWriter();
                out.write("{\"status\":\"ok\"}");
            }
            else {
                resp.setStatus(403);
                var out = resp.getWriter();
                out.write("{\"status\":\"wrong\"}");
            }
        }
        catch (Exception e) {
            resp.setStatus(400);
            var out = resp.getWriter();
            out.write(e.toString());
        }
    }
}

