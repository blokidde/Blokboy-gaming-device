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
- Method: POST
- Content-Type: application/json
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

### POST start_game.php
The API receives a player ID and creates a new game session for that player in the database. It returns the newly created game ID.

#### request
- Method: POST
- Content-Type: application/json
- Body: JSON formatted data containing the player ID.

#### request format
```json
{
  "player_id": 3
}
```

### GET get.php
The API retrieves all recorded scores from the database along with the corresponding player IDs. This endpoint is used by the frontend to display the current scores of all players.

#### request
- Method: GET
- No request body required.

#### response format
Returns a JSON array of score entries. Each entry contains:
- player_id: the ID of the player
- score_value: the score they achieved

#### example response
```json
[
  {
    "player_id": 1,
    "score_value": 45
  },
  {
    "player_id": 2,
    "score_value": 60
  }
]
```

#### response codes
if correctly sent, code: 200

if not sent correctly code of: -1

if the request doesnt have the correct fields: 400

if there is an issue with the database: 500

### functionality
The ESP32 sends joystick movement data to the API at regular intervals or after a game session.
The API validates the incoming JSON data and makes sure all required fields are in the json.
If the data is correct, it is inserted into the database, storing player movements for use in the website.
The API responds with a success or error message, allowing the ESP32 to confirm whether the request was processed correctly.

