<?php
$servername = "iot-mariadb";
$username = "root";
$password = "7YKyE8R2AhKzswfN";
$database = "mydb"; 

$conn = new mysqli($servername, $username, $password, $database);

if ($conn->connect_error) {
    die("Verbinding mislukt: " . $conn->connect_error);
}

$conn->set_charset("utf8");

echo "Verbinding geslaagd!";
?>
