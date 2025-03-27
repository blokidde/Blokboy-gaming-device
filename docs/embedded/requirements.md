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

EMBRQ#02
[Insert text explaining how you fulfilled the requirement here]

Code:
[Insert code snippet(s) proving the requirement is fulfilled here]

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