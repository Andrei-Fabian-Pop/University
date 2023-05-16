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

$json = json_decode(file_get_contents("php://input"));
$table_name = $json->table_name;
$data = (array)$json->data;
$id = $json->id;

$values = "";
foreach ($data as $key => $value) {
    $values .= "$key='$value', ";
}

$values = rtrim($values, ", ");
$sql = "UPDATE $table_name SET $values WHERE id=$id";

if ($conn->query($sql) === TRUE) {
    echo json_encode("Data updated successfully");
} else {
    echo json_encode("Error updating record: " . $conn->error);
}
