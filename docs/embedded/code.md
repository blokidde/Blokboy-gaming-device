# Embedded code

## important library's

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
```

these libraries are used for the 128x64 oled screen
```cpp
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
```
these libraries are used for the http requests, the arduinojson lib is used to create 

```cpp
#include <WiFi.h>
```
this library is used for connecting wifi

## functions

### `void setup()`
in this function we set the outputs and inputs for the entire program like this `pinMode(VERT_PIN, INPUT);`, we also connect with necessary things like wifi using this `WiFi.begin(ssid, password);`, i2c bus and the oled screen `display.begin(SSD1306_SWITCHCAPVCC, 0x3C)`. 0x3 is the i2c address for the oled screen.