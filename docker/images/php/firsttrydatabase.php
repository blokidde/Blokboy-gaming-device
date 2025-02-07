<?php
$servername = "localhost"; // Of je server-IP
$username = "root"; // Standaard in XAMPP
$password = "7YKyE8R2AhKzswfN"; // Standaard in XAMPP leeg
$database = "mydb"; // Vervang met jouw database naam

// Maak verbinding met de database
$conn = new mysqli($servername, $username, $password, $database);

// Controleer de verbinding
if ($conn->connect_error) {
    die("Verbinding mislukt: " . $conn->connect_error);
}

// Zorgt ervoor dat UTF-8 wordt gebruikt
$conn->set_charset("utf8");

// Debug: Laat een bericht zien als het werkt
// echo "Verbinding geslaagd!";
?>
