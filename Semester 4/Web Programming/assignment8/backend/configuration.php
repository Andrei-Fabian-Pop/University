<?php
$host = "127.0.0.1"; // the MySQL server hostname
$username = "andrew"; // the MySQL username
$password = "#Pa55w0rd"; // the MySQL password
$database = "master"; // the MySQL database name
$port = 3306; // the MySQL database port

// Create a new MySQL connection
$conn = new mysqli($host, $username, $password, $database, $port);

if ($conn->connect_error) {
    die("ERROR: Could not connect." . mysqli_connect_error());
}
