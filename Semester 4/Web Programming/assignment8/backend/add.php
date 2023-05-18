<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE");
header("Access-Control-Allow-Headers: *");

require_once 'configuration.php';
global $conn;

if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(200);
    exit;
}

$json = json_decode(file_get_contents("php://input"));
$table_name = $json->table_name;
$data = (array)$json->data;

$columns = implode(", ", array_keys($data));
$values = "'" . implode("', '", array_values($data)) . "'";
$sql = "INSERT INTO $table_name ($columns) VALUES ($values)";

if ($conn->query($sql) === TRUE) {
    echo json_encode("Data inserted successfully");
} else {
    echo json_encode("Error: " . $sql . "<br>" . $conn->error);
}

mysqli_close($conn);
