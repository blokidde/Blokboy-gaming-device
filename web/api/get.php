<?php
// scoreboard.php
require "db_connect.php"; // bevat de code voor db-connectie

// Query: haal scores op én koppel ze aan player_id uit Player
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
        // $row bevat ['score_value' => 123, 'player_id' => 5] enz.
        $scores[] = $row;
    }
}

// send data back as json
echo json_encode($scores);

$conn->close();
?>
