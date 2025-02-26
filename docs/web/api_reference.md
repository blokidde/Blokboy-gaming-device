# API reference

## API/ESP32

### API
The connection from the ESP32 to the API is done with an HTTP request. The HTTP request is formatted as a JSON file.

### ESP32
The ESP32 sends joystick movement data to the API via an HTTP `POST` request.

## API endpoints

### POST /api/post.php
The API receives joystick input from the ESP32 and stores it in a database.

#### request
- Method: `POST`
- Content-Type: `application/json`
- Body: JSON formatted data containing joystick movement counts.

#### request format
```json
{
    "totalup": 5,
    "totaldown": 3,
    "totalleft": 2,
    "totalright": 4
}

