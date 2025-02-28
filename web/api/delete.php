<?php
// Include the file that creates the database connection
require "db_connect.php";

// Read JSON from the request body
$json = file_get_contents("php://input");
$data = json_decode($json, true);

if (!$data) {
    // No valid JSON found
    echo json_encode([
        "status" => "error",
        "message" => "No valid JSON received"
    ]);
    $conn->close();
    exit;
}

// Check if "id" was provided
if (!isset($data['id'])) {
    echo json_encode([
        "status" => "error",
        "message" => "Missing 'id' field in JSON"
    ]);
    $conn->close();
    exit;
}

// Retrieve the id from the decoded JSON
$id = (int) $data['id'];

// Prepare a DELETE statement to remove the record by id
$stmt = $conn->prepare("DELETE FROM JoystickInput WHERE id = ?");

if (!$stmt) {
    echo json_encode([
        "status" => "error",
        "message" => "Prepare failed: " . $conn->error
    ]);
    $conn->close();
    exit;
}

// Bind the parameter (integer)
$stmt->bind_param("i", $id);

// Execute the statement
if ($stmt->execute()) {
    // Check how many rows were affected (i.e., deleted)
    if ($stmt->affected_rows > 0) {
        echo json_encode([
            "status" => "success",
            "message" => "Record with id={$id} deleted"
        ]);
    } else {
        echo json_encode([
            "status" => "error",
            "message" => "No matching record found for id={$id}"
        ]);
    }
} else {
    // Execution failed
    echo json_encode([
        "status" => "error",
        "message" => "Execute failed: " . $stmt->error
    ]);
}

// Close statement and database connection
$stmt->close();
$conn->close();
?>