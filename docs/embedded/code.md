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

### void `snakeInit()`
the snake init function is used to initialize everything needed for the snake and the first apple. first there are some variables that are set to false or 0
```cpp
 game_over = false;
  score = 0;
  totalup = 0;
  totaldown = 0;
  totalleft = 0;
  totalright = 0;
```
after this the function starts by setting the values in the struct called snake. `snake.length = 1;`the length of the snake is set to 1. this is done for several different parts of the snake struct. values for the apple struct are also set using the same principle.