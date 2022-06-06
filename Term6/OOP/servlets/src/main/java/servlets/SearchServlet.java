package servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.json.JSONArray;
import org.json.JSONObject;
import model.Course;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet(urlPatterns = {"/search"})
public class SearchServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");

        String query = req.getParameter("q");

        try {
            var cs = Course.search(query);

            var json = new JSONArray(cs);

            resp.setContentType("application/json; charset=UTF-8");
            resp.setHeader("Access-Control-Allow-Origin", "*");
            PrintWriter out = resp.getWriter();
            out.write(json.toString());

        } catch (SQLException e) {
            resp.setStatus(400);
            PrintWriter out = resp.getWriter();
            out.write(e.toString());
            e.printStackTrace();
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

    }
}
