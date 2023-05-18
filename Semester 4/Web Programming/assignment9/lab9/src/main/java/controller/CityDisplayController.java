package controller;

import domain.City;
import domain.Database;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;

@WebServlet(name = "cityDisplay", value = "/city-display")
public class CityDisplayController extends HttpServlet {
    public CityDisplayController() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        for (Cookie cookie : request.getCookies()) {
            if (cookie.getName().equals("user")) {
                var cityId = request.getSession().getAttribute("id");
                List<City> cities;
                if (cityId != null) {
                     cities = (new Database()).getAllNeighbouringCities((int) cityId);
                } else {
                    cities = (new Database()).getAllCities();
                }
                request.getSession().setAttribute("cities", cities);
                request.getRequestDispatcher("core/city-display/city-display.jsp").include(request, response);
                return;
            }
        }

        response.getWriter().println("Invalid request, you are not logged in.");
    }
}
