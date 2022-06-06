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
import org.json.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet(urlPatterns = {"/login"})
public class LoginServlet extends HttpServlet {
    // Check if the user is logged in
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=UTF-8");

        var cookies = req.getCookies();

        String sessionId = null;
        for (var cookie : cookies) {
            if (cookie.getName().equals("session_id")) {
                sessionId = cookie.getValue();
            }
        }

        PrintWriter out = resp.getWriter();
        if (sessionId == null) {
            out.write("{\"user\":null}");
        } else {
            try {
                var user = User.getUser(sessionId);
                var json = new JSONObject();
                json.put("user", new JSONObject(user));
                out.write(json.toString());
            } catch (SQLException e) {
                out.write(e.toString());
            }
        }
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

