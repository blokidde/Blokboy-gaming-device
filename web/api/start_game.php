<?php
// Include database connection
require "db_connect.php";

// Read JSON input
$json = file_get_contents("php://input");
$data = json_decode($json, true);

// Check if start is set in the JSON request
if ($data && isset($data['start']) && $data['start'] == 1) {
    
    // Insert a new game into the CurrentGame column start
    $stmt = $conn->prepare("INSERT INTO CurrentGame (start) VALUES (1)");
    
    if ($stmt->execute()) {
        echo json_encode([
            "status" => "success",
            "message" => "Game started successfully"
        ]);
    } else {
        echo json_encode(["status" => "error", "message" => "Failed to start game"]);
    }
    $stmt->close();
} else {
    echo json_encode(["status" => "error", "message" => "Invalid input"]);
}

// Close the database connection
$conn->close();
?>
