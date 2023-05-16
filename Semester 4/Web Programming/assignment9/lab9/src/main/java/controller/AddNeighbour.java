package controller;

import domain.Database;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

public class AddNeighbour extends HttpServlet {
    public AddNeighbour() {
        super();
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try {
            new Database().addCityConnection(Integer.parseInt(request.getParameter("city1")), Integer.parseInt(request.getParameter("city2")));
        } catch (Exception e) {
            response.sendError(418, e.getMessage());
        }
    }
}
