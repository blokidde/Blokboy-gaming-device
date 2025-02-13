<?php
require "db_connect.php";

$json = file_get_contents("php://input");
$data = json_decode($json, true);

if($data){
    $player_id = $data['username'];
    // $score = $data['score'];
    // $game_id = $data['game_id']; 

    $stmt = $conn->prepare("INSERT INTO Player (username) VALUES (?)");
    $stmt->bind_param("i", $username);
    $stmt->execute();

    $stmt->close();
} else {
    echo json_encode(["status" => "error", "message" => "nothing recieved"]);
}

$conn->close();
?>