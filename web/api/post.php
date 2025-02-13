<?php
require "db_connect.php";

$json = file_get_contents("php://input");
$data = json_decode($json, true);

if($data){
    $totalup = $data['totalup'];
    $totaldown = $data['totaldown'];
    $totalright = $data['totalright'];
    $totalleft = $data['totalleft'];

    $stmt = $conn->prepare("INSERT INTO JoystickInput (totalup, totaldown, totalright, totalleft) VALUES ( ?, ?, ?, ?)");
    $stmt->bind_param("iiii", $totalup, $totalleft, $totalleft, $totalleft);
    if ($stmt->execute()) {
        echo json_encode([
            "status" => "success",
            "message" => "Data inserted",
            "inserted_data" => [
                "totalup"    => $totalup,
                "totaldown"  => $totaldown,
                "totalright" => $totalright,
                "totalleft"  => $totalleft
            ]
        ]);
    } else {
        // Fout bij uitvoeren
        echo json_encode([
            "status" => "error",
            "message" => "Execute failed: " . $stmt->error
        ]);
    }
}
$stmt->close();
$conn->close();
?>

