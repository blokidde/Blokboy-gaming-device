<?php
// Include the file that creates the $conn database connection
require "db_connect.php";

// Read raw JSON from the request body
$json = file_get_contents("php://input");
// Decode the JSON into a PHP array/object
$data = json_decode($json, true);

if ($data) {
    // Extract the fields from the decoded JSON, met fallback naar 0 als een waarde ontbreekt
    $totalup = $data['totalup'] ?? 0;
    $totaldown = $data['totaldown'] ?? 0;
    $totalright = $data['totalright'] ?? 0;
    $totalleft = $data['totalleft'] ?? 0;
    $score_value = $data['score_value'] ?? 0;

    // Start a database transaction for rollbacks if something goes wrong
    $conn->begin_transaction();

    try {
        // Prepare and execute first INSERT for JoystickInput
        $stmt1 = $conn->prepare("INSERT INTO JoystickInput (totalup, totaldown, totalright, totalleft) VALUES (?, ?, ?, ?)");
        $stmt1->bind_param("iiii", $totalup, $totaldown, $totalright, $totalleft);
        $stmt1->execute();
        $stmt1->close();

        // Prepare en execute the second INSERT for Score
        $stmt2 = $conn->prepare("INSERT INTO Score (score_value) VALUES (?)");
        $stmt2->bind_param("i", $score_value);
        $stmt2->execute();
        $stmt2->close();

        // commit whe both statements succeed
        $conn->commit();

        // send succesful JSON-response back
        echo json_encode([
            "status" => "success",
            "message" => "Data inserted",
            "inserted_data" => [
                "totalup" => $totalup,
                "totaldown" => $totaldown,
                "totalright" => $totalright,
                "totalleft" => $totalleft,
                "score_value" => $score_value
            ]
        ]);
    } catch (Exception $e) {
        // rollback transaction if error occurs
        $conn->rollback();
        echo json_encode([
            "status" => "error",
            "message" => "Execute failed: " . $e->getMessage()
        ]);
    }
} else {
    // no correct json error handler
    echo json_encode([
        "status" => "error",
        "message" => "No valid JSON received"
    ]);
}

// close database connection
$conn->close();
?>
