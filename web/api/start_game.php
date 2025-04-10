<?php
/**
 * File: start_game.php
 * Author: Jurriaan Egmond
 * Date: 2025-04-10
 * Description:
 *   This endpoint creates a new game session in the database for a player.
 *   It is called by the ESP32 when a new game starts.
 *   If no existing player is provided, a new player is generated.
 *   Returns a JSON object containing player_id and game_id.
 */
// Include database connection
require "db_connect.php";

// Read raw JSON input
$json = file_get_contents("php://input");
$data = json_decode($json, true);

// Check if valid JSON and 'generate' equals 1
if ($data && isset($data['generate']) && $data['generate'] == 1) {
    
    // Maak een nieuwe rij in Player (generate = 1)
    $stmtPlayer = $conn->prepare("INSERT INTO Player (generate) VALUES (1)");
    if ($stmtPlayer->execute()) {
        // Haal de nieuw gegenereerde player_id op
        $player_id = $stmtPlayer->insert_id;
        
        // Voeg een nieuwe rij toe in CurrentGame (met de net aangemaakte player_id)
        $stmtGame = $conn->prepare("INSERT INTO CurrentGame (player_id) VALUES (?)");
        $stmtGame->bind_param("i", $player_id);
        
        if ($stmtGame->execute()) {
            // Haal de nieuw gegenereerde game_id op
            $game_id = $stmtGame->insert_id;

            // Stuur JSON-response terug met player_id en game_id
            echo json_encode([
                "status" => "success",
                "message" => "Player and Game created",
                "player_id" => $player_id,
                "game_id" => $game_id
            ]);
        } else {
            echo json_encode([
                "status" => "error",
                "message" => "Failed to create a new CurrentGame record"
            ]);
        }
        $stmtGame->close();
    } else {
        echo json_encode([
            "status" => "error",
            "message" => "Failed to create a new Player record"
        ]);
    }
    $stmtPlayer->close();
} else {
    echo json_encode([
        "status" => "error",
        "message" => "Invalid input"
    ]);
}

$conn->close();
?>
