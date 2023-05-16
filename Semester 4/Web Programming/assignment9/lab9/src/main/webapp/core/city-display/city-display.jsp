<%--
  Created by IntelliJ IDEA.
  User: andrew
  Date: 14/05/2023
  Time: 14:05
--%>
<%@ page import="java.util.List" %>
<%@ page import="domain.City" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>City Display</title>
    <link rel="stylesheet" type="text/css" href="${pageContext.request.contextPath}/core/city-display/city-display.pcss">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <div class="main">
        <form action="logout"><button>Logout</button></form>
        <form>
            <label id="destinations">
                <select id="destination0" onchange="historyChanged()">
                    <%
                        List<City> cities = (List<City>) request.getSession().getAttribute("cities");
                        for (City city : cities) {
                            out.println("<option value=\"" + city.getId() + "\">" + city.getName() + "</option>");
                        }
                    %>
                </select>
            </label>

            <button type="button" onclick="addDestination()">Add Destination</button>
            <button type="submit">Final Destination</button>
        </form>
    </div>
</body>
<footer>
    <script src="${pageContext.request.contextPath}/core/city-display/city-display.js"></script>
</footer>
</html>
