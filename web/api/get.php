<?php
require "db_connect.php";

$json = file_get_contents("php://input");
$data = json_decode($json, true);

if($data){
    $player_id = $data['player_id'];
    $score = $data['score'];
    $game_id = $data['game_id']; 

    $stmt = $conn->prepare("INSERT INTO Score (player_id, game_id, score_value) VALUES (?, ?, ?)");
    $stmt->bind_param("iii", $player_id, $game_id, $score);
    $stmt->close();
} else {
    echo json_encode(["status" => "error", "message" => "nothing recieved"]);
}

$conn->close();
?>