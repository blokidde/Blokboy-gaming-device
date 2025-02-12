<?php
require 'db_connect.php';

$result = $conn->query("SELECT * FROM Player");
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Blockboy handheld gaming device</title>
    <link rel="stylesheet" href="css/style.css">
  </head>
  <body>
	<h1>Blockboy</h1>
    <h2>Player</h2>
      <ul>
        <?php while ($row = $result->fetch_assoc()) { ?>
          <li><?php echo "ID: " . $row['player_id'] . " - Naam: " . $row['username']; ?></li>
        <?php } ?>
      </ul>
  </body>
</html>

<?php
$conn->close();
?>