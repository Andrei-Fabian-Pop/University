<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

$host = "127.0.0.1"; // the MySQL server hostname
$username = "andrew"; // the MySQL username
$password = "#Pa55w0rd"; // the MySQL password
$database = "master"; // the MySQL database name
$port = 3306; // the MySQL database port

// Create a new MySQL connection
$conn = new mysqli($host, $username, $password, $database, $port);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

function select_specific_data($conn, $table_name, $key, $value)
{
    $sql = "SELECT * FROM $table_name WHERE $key=$value";
    $result = $conn->query($sql);

    $data = array();
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }

    return $data;
}

function pretty_print($conn)
{
    $result = array();
    $index = 0;

    $all_recipes = "SELECT * FROM Recipes";
    $all_recipes_result = $conn->query($all_recipes);

    while ($row = $all_recipes_result->fetch_assoc()) {
        $result[$index] = array('name' => $row['name'], 'description' => $row['description'], 'author' => $row['author']);
        $instructions = "SELECT * FROM RecipeInstructions WHERE recipe=" . $row['id'];
        $instructions_result = $conn->query($instructions);

        while ($instruct = $instructions_result->fetch_assoc()) {
            $ingredients = "SELECT * FROM Ingredients WHERE id=" . $instruct['ingredient'];
            $ingredients_result = $conn->query($ingredients);

            $result[$index]['data'][] = array(); // continue here
        }

        ++$index;
    }
    return $result;
}

function select_data($conn, $table_name)
{
    global $conn;

    $sql = "SELECT * FROM $table_name";
    $result = $conn->query($sql);

    $data = array();
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }

    return $data;
}

function insert_data($conn, $table_name, $data)
{
    $columns = implode(", ", array_keys($data));
    $values = "'" . implode("', '", array_values($data)) . "'";
    $sql = "INSERT INTO $table_name ($columns) VALUES ($values)";

    if ($conn->query($sql) === TRUE) {
        return "Data inserted successfully";
    } else {
        return "Error: " . $sql . "<br>" . $conn->error;
    }
}

function delete_data($conn, $table_name, $id)
{
    $sql = "DELETE FROM $table_name WHERE id=$id";

    if ($conn->query($sql) === TRUE) {
        return "Data deleted successfully";
    } else {
        return "Error deleting record: " . $conn->error;
    }
}

// Update data in the database
function update_data($conn, $table_name, $id, $data)
{
    $values = "";
    foreach ($data as $key => $value) {
        $values .= "$key='$value', ";
    }
    $values = rtrim($values, ", ");
    $sql = "UPDATE $table_name SET $values WHERE id=$id";

    if ($conn->query($sql) === TRUE) {
        return "Data updated successfully";
    } else {
        return "Error updating record: " . $conn->error;
    }
}

if (isset($_GET['action']) && isset($_GET['table_name']) && isset($_GET['key']) && isset($_GET['value'])) {
    if ($_GET['action'] == 'select_specific_data') {
        echo json_encode(select_specific_data($conn, $_GET['table_name'], $_GET['key'], $_GET['value']));
    }
}

if (isset($_GET['action']) && isset($_GET['table_name'])) {
    if ($_GET['action'] == 'select_data') {
        echo json_encode(select_data($conn, $_GET['table_name']));
    }
}

if (isset($_POST['action']) && isset($_POST['table_name']) && isset($_POST['id']) && isset($_POST['data'])) {
    if ($_POST['action'] == 'update_data') {
        echo json_encode(update_data($conn, $_POST['table_name'], $_POST['id'], $_POST['data']));
    }
}

if (isset($_POST['action']) && isset($_POST['table_name']) && isset($_POST['data'])) {
    if ($_POST['action'] == 'insert_data') {
        echo json_encode(insert_data($conn, $_POST['table_name'], $_POST['data']));
    }
}

if (isset($_POST['action']) && isset($_POST['table_name']) && isset($_POST['id'])) {
    if ($_POST['action'] == 'delete_data') {
        echo json_encode(delete_data($conn, $_POST['table_name'], $_POST['id']));
    }
}

if (isset($_GET['action'])) {
    if ($_GET['action'] == 'pretty_print') {
        echo json_encode(pretty_print($conn));
    }
}
