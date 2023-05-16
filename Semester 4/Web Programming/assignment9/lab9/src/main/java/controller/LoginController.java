package controller;

import domain.Database;
import domain.User;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet(name = "login", value = "/login")
public class LoginController extends HttpServlet {
    public LoginController() {
        super();
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username.equals("")) {
            request.getSession().setAttribute("error", "Username must not be null!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else if (password.isEmpty()) {
            request.getSession().setAttribute("error", "Password must not be null!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else if (password.length() < 3) {
            request.getSession().setAttribute("error", "Password is not strong enough! It must have more than 2 characters!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else {
            Database dbManager = new Database();
            User user = dbManager.authenticate(username, password);
            if (user != null) {
                response.addCookie(new Cookie("user", user.getName()));
                response.sendRedirect("city-display");
            } else {
                request.getSession().setAttribute("error", "Username or password invalid!");
                request.getRequestDispatcher("login.jsp").include(request, response);
            }
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        request.getRequestDispatcher("login/login.jsp").include(request, response);
    }
}