<?php
// Include the file that creates the $conn database connection
require "db_connect.php";

// Prepare a SELECT query for the table JoystickInput
$sql = "SELECT totalup, totaldown, totalright, totalleft FROM JoystickInput";

// Execute the query
$result = $conn->query($sql);

if (!$result) {
    // If the query fails, give an error
    echo json_encode([
        "status" => "error",
        "message" => "Query failed: " . $conn->error
    ]);
    $conn->close();
    exit;
}

// Fetch all rows into array
$data = [];
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

// Check if any rows get back
if (count($data) === 0) {
    echo json_encode([
        "status" => "success",
        "data" => [],
        "message" => "No rows found"
    ]);
} else {
    echo json_encode([
        "status" => "success",
        "data" => $data
    ]);
}

// Close the database connection
$conn->close();
?>
