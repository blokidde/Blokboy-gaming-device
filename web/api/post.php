<?php
require "db_connect.php";

$json = file_get_contents("php://input");
$data = json_decode($json, true);

if($data){
    $totalup = $data['totalup'];
    $totaldown = $data['totaldown'];
    $totalright = $data['totalright'];
    $totalleft = $data['totalleft'];

    $stmt = $conn->prepare("INSERT INTO JoystickInput (totalup, totaldown, totalright, totalleft) VALUES (????)");
    $stmt->bind_param("iiii", $totalup, $totaldown, $totalleft, $totalleft);
    $stmt->execute();
    $stmt->close();
} else {
    echo json_encode(["status" => "error", "message" => "nothing recieved"]);
}

$conn->close();
?>