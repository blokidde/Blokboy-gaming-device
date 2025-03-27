# Requirements


# requirements EMBRQ#01
The embedded device acts as a client and sends measured sensor data to the application backend over http or https.

## EMBRQ#01
The ESP32 sends sensor data to a webserver using HTTP. It acts like a client and sends the number of times the joystick was moved up, down, left, and right. This is done using WiFi and a POST request. The data is sent as a JSON string to the backend.

### Code:
```cpp
HTTPClient httpClient;
httpClient.begin(client, url);

StaticJsonDocument<200> doc;
doc["totalup"] = totalup;
doc["totaldown"] = totaldown;
doc["totalleft"] = totalleft;
doc["totalright"] = totalright;

String jsonString;
serializeJson(doc, jsonString);

int httpcode = httpClient.POST(jsonString);
```

# requirements EMBRQ#02
The embedded device also acts as a server and receives status messages from the application backend over http or https.

## EMBRQ#02
The ESP32 works as a server. It waits for HTTP requests from the backend. When the backend sends a request to the /debug endpoint, the ESP32 sees this and runs the debug() function. This way, it can receive status messages or commands from the backend over HTTP.

### code
```cpp
WiFiClient client = server.available();

if (client) {
  String request = "";
  while (client.available()) {
    char c = client.read();
    request += c;
    if (c == '\n') break;
  }

  if (request.indexOf("GET /debug") >= 0) {
    debug();
  }
}
```

# requirements EMBRQ#03
The embedded device contains at least two types of input sensors (e.g. LDR, buttons, joystick, capacitive touch, etc.).

## EMBRQ#03
The ESP32 uses two types of input sensors:
- A joystick to control the snake's movement (up, down, left, right).
- Buttons to interact with the game, like starting or restarting.

The joystick is read using analog input pins, and the buttons are read using digital input pins.

### code
example of joystick code:
```cpp
if (vert < DOWNTHRES && snake.direction_y != -1) {
    snake.direction_x = 0;
    snake.direction_y = 1;
}
```

example of button code:
```cpp
while(digitalRead(BUTTON_2_PIN)){
    delay(20);
}
```

# requirements EMBRQ#04
The embedded device contains at least two types of visual and/or sensory outputs (e.g. LED, LED Matrix, 7-segment display, motor, servo, actuator, LCD-screen, buzzer, etc.).

## EMBRQ#04
The ESP32 has two types of outputs:

- An lcd display (ILI9341) that displays the snake game
- A piezo buzzer that makes sound during the debug test and during the game

### code
example for display:
```cpp
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

display.setTextSize(1);
display.setTextColor(ILI9341_WHITE);
display.fillScreen(ILI9341_BLACK);
```
example for buzzer:
```cpp
tone(BUZZER_PIN, 1000, 100);
```
EMBRQ#05
[Insert text explaining how you fulfilled the requirement here]

Code:
[Insert code snippet proving the requirement is fulfilled here]