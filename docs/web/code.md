# Web Code

## PHP
### db_connect.php
a single file for connecting to the database using mysqli. this file is used in all the other php files.

### get.php
Returns a list of all game scores stored in the database by connecting to the database, executing a SQL query with SELECT, returns a JSON array.

### insert.php
Receives statistics from the ESP32 and puts them into the database.
```json
{
  "game_id": 123,
  "totalup": 10,
  "totaldown": 8,
  "totalleft": 5,
  "totalright": 7,
  "score_value": 15
}
```
this is what the expected json looks like, the function parses this, validates it and puts it into the score table with and INSERT INTO query

## JavaScript
JS handles the communication between the webpage and the server (PHP backend) as well as sending debug requests to the ESP32 device.

### fetchScores()
This function retrieves all game scores from the backend API (get.php) and dynamically updates the HTML table.
```JS
fetch('api/get.php')
.then(response => response.json())
.then(data => {
// Updates DOM with new data
});
```
this function first makes a GET request to the get.php endpoint. afther this is parses the json and updates the table with the data.

### sendRequestToEsp32()
This function sends a debug request to the ESP32 device.

```JS
fetch('https://145.109.225.167/debug', { method: 'GET' })
```

makes a GET request to the esp32's ip address webserver