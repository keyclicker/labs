package servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import model.Session;
import model.User;

import java.io.IOException;

@WebServlet(urlPatterns = {"/signup"})
public class SignupServlet extends HttpServlet {
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

            var session = Session.createNew(user.getUsername());
            session.insert();

            resp.addCookie(new Cookie("value", session.getValue()));

            var out = resp.getWriter();
            out.write("{\"status\":\"ok\"}");
        }
        catch (Exception e) {
            resp.setStatus(400);
            var out = resp.getWriter();
            out.write(e.toString());
        }
    }
}
