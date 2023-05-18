package domain;

import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class Database {
    private static final String connectionString = "jdbc:mysql://localhost:3306/lab9web";
    private static final String dbuser = "andrew";
    private static final String password = "#Pa55w0rd";

    public Database() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }

    public User getUserFromName(String username) {
        User user = null;
        String statement = "select * from users where name='" + username + "';";
        try (var connection = DriverManager.getConnection(connectionString, dbuser, password);
             var preparedStatement = connection.prepareStatement(statement);
             var rs = preparedStatement.executeQuery()) {
            if (rs.next())
                user = new User(rs.getInt("id"), rs.getString("name"), rs.getString("password"));
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return user;
    }

    public User authenticate(String username, String password) {
        User user = getUserFromName(username);
        if (user != null && user.getPassword().equals(password))
            return user;
        return null;
    }

    public List<City> getAllCities() {
        List<City> cities = new ArrayList<>();
        String statement = "select * from cities";
        try (var connection = DriverManager.getConnection(connectionString, dbuser, password);
             var preparedStatement = connection.prepareStatement(statement);
             var rs = preparedStatement.executeQuery()) {
            while (rs.next())
                cities.add(new City(rs.getInt("id"), rs.getString("name")));
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return cities;
    }

    public List<City> getAllNeighbouringCities(int cityId) {
        List<City> cities = new ArrayList<>();
        String statement = "SELECT c.* FROM cities c JOIN neighboring_cities nc ON c.id = nc.city OR c.id = nc.neighbour WHERE (nc.city = " + cityId + " OR nc.neighbour = " + cityId + ") AND c.id != " + cityId + ";";
        try (var connection = DriverManager.getConnection(connectionString, dbuser, password);
             var preparedStatement = connection.prepareStatement(statement);
             var rs = preparedStatement.executeQuery()) {
            while (rs.next())
                cities.add(new City(rs.getInt("id"), rs.getString("name")));
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return cities;
    }

    public void addCity(String name) {
        String statement = "INSERT INTO cities (name) VALUES ('" + name + "')";
        try {
            var connection = DriverManager.getConnection(connectionString, dbuser, password);
            var preparedStatement = connection.prepareStatement(statement);
            preparedStatement.executeQuery();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }

    public void addCityConnection(int city1, int city2) throws Exception {
        if (city1 == city2) {
            throw new Exception("Cannot route to the same city");
        }

        if (city1 > city2) {
            city1 = (city1 + city2) - (city2 = city1);
        }

        String statement = "INSERT INTO neighboring_cities (city, neighbour) VALUES (" + city1 + ", " + city2 + ")";
        try {
            var connection = DriverManager.getConnection(connectionString, dbuser, password);
            var preparedStatement = connection.prepareStatement(statement);
            preparedStatement.executeQuery();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }
}
