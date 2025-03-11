# API reference

## API/ESP32

### API
The API handles communication between the ESP32 and the database. The ESP32 sends data to the API using an HTTP request, formatted as a JSON file. The API processes this data and stores it in the database for further analysis.

### ESP32
The ESP32 collects joystick movement data and sends it to the API through an HTTP POST request. This allows the system to track player input and use it for game analytics or debugging.

## API endpoints

### POST post.php
The API receives joystick input from the ESP32 and stores it in a database.

#### request
- Method: `POST`
- Content-Type: `application/json`
- Body: JSON formatted data containing joystick movement counts.

#### request format
```json
{   
    "game_id": 31,
    "totalup": 5,
    "totaldown": 3,
    "totalleft": 2,
    "totalright": 4,
    "score": 9
}
```

#### response
if correctly sent, code: 200.

if not sent correctly code of: -1

if the request doesnt have the correct fields: 400

if there is an issue with the database: 500

### functionality
The ESP32 sends joystick movement data to the API at regular intervals or after a game session.
The API validates the incoming JSON data and makes sure all required fields are in the json.
If the data is correct, it is inserted into the database, storing player movements for use in the website.
The API responds with a success or error message, allowing the ESP32 to confirm whether the request was processed correctly.

