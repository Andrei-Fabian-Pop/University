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
    <link rel="stylesheet" type="text/css" href="${pageContext.request.contextPath}/register/register.css">
</head>
<body>
<div class="register-form">
    <form>
        <h1>Register</h1>
        <div class="content">
            <div class="input-field">
                <label>
                    <input type="email" placeholder="Username" autocomplete="nope">
                </label>
            </div>
            <div class="input-field">
                <label>
                    <input type="password" placeholder="Password" autocomplete="new-password">
                </label>
            </div>
            <a href="#" class="link">Forgot Your Password?</a>
        </div>
        <div class="action">
            <button>Register</button>
            <button id="loginButton">Log in</button>
        </div>
    </form>
</div>

</body>
</html>
