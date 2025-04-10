<?php
/**
 * File: insert.php
 * Author: Jurriaan Egmond
 * Date: 2025-04-10
 * Description:
 *   This endpoint receives game data from the ESP32 after a session ends.
 *   It expects a JSON payload with game_id, score, and joystick statistics.
 *   The data is validated and inserted into the database.
 *   Returns a JSON response with success or error status.
 */
// Include the file that connects to the database
require "db_connect.php";

// Read raw JSON from the request
$json = file_get_contents("php://input");
$data = json_decode($json, true);

if ($data) {
    // Extract data from JSON
    $game_id = $data['game_id']; // Now we expect game_id from the request
    $totalup = $data['totalup'];
    $totaldown = $data['totaldown'];
    $totalright = $data['totalright'];
    $totalleft = $data['totalleft'];
    $score_value = $data['score_value'];

    try {
        // Check if game_id exists before inserting data
        $checkGame = $conn->prepare("SELECT game_id FROM CurrentGame WHERE game_id = ?");
        $checkGame->bind_param("i", $game_id);
        $checkGame->execute();
        $checkGame->store_result();
        if ($checkGame->num_rows == 0) {
            echo json_encode(["status" => "error", "message" => "Game ID does not exist"]);
            exit();
        }
        $checkGame->close();

        // Insert Joystick Input linked to game_id
        $stmt1 = $conn->prepare("INSERT INTO JoystickInput (game_id, totalup, totaldown, totalright, totalleft) VALUES (?, ?, ?, ?, ?)");
        $stmt1->bind_param("iiiii", $game_id, $totalup, $totaldown, $totalright, $totalleft);
        $stmt1->execute();
        $stmt1->close();

        // Insert Score linked to game_id
        $stmt2 = $conn->prepare("INSERT INTO Score (game_id, score_value) VALUES (?, ?)");
        $stmt2->bind_param("ii", $game_id, $score_value);
        $stmt2->execute();
        $stmt2->close();

        echo json_encode([
            "status" => "success",
            "message" => "Data inserted successfully",
            "inserted_data" => [
                "game_id" => $game_id,
                "totalup" => $totalup,
                "totaldown" => $totaldown,
                "totalright" => $totalright,
                "totalleft" => $totalleft,
                "score_value" => $score_value
            ]
        ]);
    } catch (Exception $e) {
        echo json_encode(["status" => "error", "message" => "Execute failed: " . $e->getMessage()]);
    }
} else {
    echo json_encode(["status" => "error", "message" => "No valid JSON received"]);
}

// Close database connection
$conn->close();
?>
