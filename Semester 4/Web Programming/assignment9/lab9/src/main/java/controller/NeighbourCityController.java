package controller;

import com.mysql.cj.xdevapi.JsonArray;
import domain.City;
import domain.Database;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

@WebServlet(name = "neighbourDisplay", value = "/neighbour-display")
public class NeighbourCityController extends HttpServlet {
    public NeighbourCityController() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        for (Cookie cookie : request.getCookies()) {
            if (cookie.getName().equals("user")) {
                int cityId = Integer.parseInt(request.getParameter("id"));
                List<City> cities;
                cities = (new Database()).getAllNeighbouringCities(cityId);
//                System.out.println(cities.stream().map(City::toJSON).collect(Collectors.joining(",")));
                response.getWriter().println("[" + cities.stream().map(City::toJSON).collect(Collectors.joining(",")) + "]");
                return;
            }
        }

        response.getWriter().println("Invalid request, you are not logged in.");
    }
}
