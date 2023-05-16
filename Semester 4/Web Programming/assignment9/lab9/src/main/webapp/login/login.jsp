<%--
  Created by IntelliJ IDEA.
  User: andrew
  Date: 13/05/2023
  Time: 03:32
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html lang="en" >
<head>
    <meta charset="UTF-8">
    <title>Login</title>
    <link rel="stylesheet" type="text/css" href="${pageContext.request.contextPath}/login/login.css">
</head>
<body>
<div class="login-form">
    <form action="login" method="post">
        <h1>Login</h1>
        <div class="content">
            <div class="input-field">
                <label>
                    <input name="username" type="text" placeholder="Username" autocomplete="nope" required>
                </label>
            </div>
            <div class="input-field">
                <label>
                    <input name="password" type="password" placeholder="Password" autocomplete="new-password" required>
                </label>
            </div>
            <a href="#" class="link">Forgot Your Password?</a>
        </div>
        <div class="action">
            <button id="registerButton">Register</button>
            <button>Log in</button>
        </div>
    </form>
</div>

</body>
</html>
