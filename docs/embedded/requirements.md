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
The ESP32 also works as a server. It waits for HTTP requests from the backend. When the backend sends a request to the /debug endpoint, the ESP32 sees this and runs the debug() function. This way, it can receive status messages or commands from the backend over HTTP.

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

EMBRQ#03
[Insert text explaining how you fulfilled the requirement here]

Code:
[Insert code snippet(s) proving the requirement is fulfilled here]

EMBRQ#04
[Insert text explaining how you fulfilled the requirement here]

Code:
[Insert code snippet proving the requirement is fulfilled here]

EMBRQ#05
[Insert text explaining how you fulfilled the requirement here]

Code:
[Insert code snippet proving the requirement is fulfilled here]