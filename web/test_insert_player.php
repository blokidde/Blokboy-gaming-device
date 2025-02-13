<?php
$servername = "iot-mariadb";
$username = "root";
$password = "7YKyE8R2AhKzswfN";
$database = "mydb"; 

$conn = new mysqli($servername, $username, $password, $database);

// Hardcoded spelernaam
$username = "JurriaanTest2";

// Gebruik een prepared statement om SQL-injecties te voorkomen
$stmt = $conn->prepare("INSERT INTO Player (username) VALUES (?)");
$stmt->bind_param("s", $username); // "s" betekent string

if ($stmt->execute()) {
    echo "Speler '$username' succesvol toegevoegd!";
} else {
    echo "Fout bij toevoegen: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>
