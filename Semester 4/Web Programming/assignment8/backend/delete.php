<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, PATCH, DELETE");
header("Access-Control-Allow-Headers: *");

if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(200);
    exit;
}

require_once 'configuration.php';
global $conn;

$table_name = $_GET["table_name"];
$id = $_GET["id"];

$sql = "DELETE FROM $table_name WHERE id=$id";

if ($conn->query($sql) === TRUE) {
    echo json_encode("Data deleted successfully");
} else {
    echo json_encode("Error deleting record: " . $conn->error);
}
