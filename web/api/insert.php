<?php
// Include the file that creates the $conn database connection
require "db_connect.php";

// Read raw JSON from the request body
$json = file_get_contents("php://input");
// Decode the JSON into a PHP array/object
$data = json_decode($json, true);

if ($data) {
    // Extract the four fields from the decoded JSON
    $totalup = $data['totalup'];
    $totaldown = $data['totaldown'];
    $totalright = $data['totalright'];
    $totalleft = $data['totalleft'];

    // Prepare an INSERT statement
    $stmt = $conn->prepare("INSERT INTO JoystickInput (totalup, totaldown, totalright, totalleft) VALUES (?, ?, ?, ?)");

    // Bind parameters to the INSERT statement
    $stmt->bind_param("iiii", $totalup, $totaldown, $totalright, $totalleft);

    // Execute and check for success
    if ($stmt->execute()) {
        echo json_encode([
            "status" => "success",
            "message" => "Data inserted",
            "inserted_data" => [
                "totalup" => $totalup,
                "totaldown" => $totaldown,
                "totalright" => $totalright,
                "totalleft" => $totalleft
            ]
        ]);
    } else {
        // Execution failed, show the error
        echo json_encode([
            "status" => "error",
            "message" => "Execute failed: " . $stmt->error
        ]);
    }

    // Close the statement
    $stmt->close();
} else {
    // If no valid JSON data found in the request
    echo json_encode([
        "status" => "error",
        "message" => "No valid JSON received"
    ]);
}

// Close the database connection
$conn->close();
?>