<?php
require 'db_connect.php'; // Zorg ervoor dat dit je databaseverbinding bevat

// Hardcoded spelernaam
$username = "JurriaanTest";

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
