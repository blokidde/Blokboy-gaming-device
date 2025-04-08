# Web Code

## PHP

## JavaScript
JS handles the communication between the webpage and the server (PHP backend) as well as sending debug requests to the ESP32 device.

### fetchscores()
This function retrieves all game scores from the backend API (get.php) and dynamically updates the HTML table.
```JS
fetch('api/get.php')
.then(response => response.json())
.then(data => {
// Updates DOM with new data
});
```
this function first makes a GET request to the get.php endpoint. afther this is parses the json and updates the table with the data.

### sendrequesttoesp32()
