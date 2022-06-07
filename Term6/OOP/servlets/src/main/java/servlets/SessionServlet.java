package servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import model.User;
import org.json.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet(urlPatterns = {"/session"})
public class SessionServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=UTF-8");

        PrintWriter out = resp.getWriter();

        try {
            var user = User.fromCookies(req.getCookies());
            if (user == null) {
                resp.setStatus(400);
                out.write("{\"user\":\"null\"}");
            } else {
                var json = new JSONObject();
                json.put("user", new JSONObject(user));
                out.write(json.toString());
            }
        } catch (Exception e) {
            resp.setStatus(400);
            out.write("{\"user\":\"null\"}");
        }
    }
}
