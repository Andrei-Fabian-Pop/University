package controller;

import domain.Database;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class AddCity extends HttpServlet {
    public AddCity() {
        super();
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        new Database().addCity(request.getParameter("name"));
    }
}
