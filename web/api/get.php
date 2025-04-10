<?php
/**
 * File: get.php
 * Author: Jurriaan Egmond
 * Date: 2025-04-10
 * Description:
 *   This endpoint retrieves all game scores from the database.
 *   It is called by the frontend to display player scores.
 *   Returns a JSON array with player_id and score_value fields.
 */
// connection file
require "db_connect.php";

// SQL query
$query = "
    SELECT s.score_value, p.player_id
    FROM Score s
    JOIN CurrentGame c ON s.game_id = c.game_id
    JOIN Player p ON c.player_id = p.player_id
    ORDER BY s.score_value DESC
    LIMIT 15
";

$result = $conn->query($query);
$scores = [];

if ($result && $result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $scores[] = $row;
    }
}

echo json_encode($scores);

// close connection to database
$conn->close();
?>
