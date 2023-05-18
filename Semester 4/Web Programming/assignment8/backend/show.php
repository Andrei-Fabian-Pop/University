<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

require_once 'configuration.php';
global $conn;

$table_name = $_GET["table_name"];
$offset = $_GET["offset"];
$limit = $_GET["limit"];
$filter = $_GET["filter"];
$key = $_GET["key"];

$sql = "SELECT * FROM $table_name";

if (!empty($filter) && !empty($key)) {
    $sql .= " WHERE $key LIKE '%$filter%'";
}

$sql .= " LIMIT $offset, $limit;";
$result = $conn->query($sql);

$data = array();
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

echo json_encode($data);
mysqli_close($conn);
