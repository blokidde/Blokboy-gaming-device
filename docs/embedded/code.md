# Embedded code

## important library's

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
```

these libraries are used for the ILI9341 display
```cpp
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
```
these libraries are used for the https requests, the arduinojson lib is used to create 

```cpp
#include <WiFi.h>
```
this library is used for connecting wifi

## functions

### `void setup()`
in this function we set the outputs and inputs for the entire program like this `pinMode(VERT_PIN, INPUT);`, we also connect with necessary things like wifi using this:
```cpp
WiFiManager wifiManager;
if (!wifiManager.autoConnect("ESP32-Setup")) {
  Serial.println("Failed to connect, restarting...");
  delay(3000);
  ESP.restart();
}
```
for the initialization of the display we use this:
```cpp
SPI.begin(TFT_CLK, -1, TFT_MOSI);
display.begin();
```

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

### void creategame()
the creategame function clears the screen, draws the apple at its position, draws each segment of the snake, and finally updates the display so you can see everything on the OLED screen. It uses a grid system, so it multiplies the apple’s and snake’s coordinates by the block size to place them at the right spots in pixels.

```cpp
display.fillRect(applex, appley, BLOCKSIZE, BLOCKSIZE, ILI9341_RED);
```
this code is used to create apples, in the code we use blocksize. the block size is the size of every object. this is done so that the snake and apple arent way too small. the block size is 8, the ILI9341 is 320x240 pixels

```cpp
for (int i = 0; i < snake.length; i++)
{
  int x = snake.segments[i].x * BLOCKSIZE;
  int y = snake.segments[i].y * BLOCKSIZE;
  display.fillRect(x, y, BLOCKSIZE, BLOCKSIZE, ILI9341_GREEN);
}
```
this code uses the same principle to create the starting segments of the snake. they are also made from blocks that are 8x8 pixels.

### void drawSnake()
The drawSnake function moves the snake’s head in its current direction and checks if it hits a wall or its own segments. If it eats an apple, the snake grows longer and the apple is moved to a new random location. Otherwise, it just moves forward. If the snake collides with anything, the game ends.

```cpp
int newHeadX = snake.segments[0].x + snake.direction_x;
int newHeadY = snake.segments[0].y + snake.direction_y;
```
in this code snippet you can see how the new head of the x and y are calculated. first you take the first point of the segments array. this is the old head position. after this you add the direction, this direction comes from the joystick input. 


```cpp
if (newHeadX < 0 || newHeadX >= ROWSX || newHeadY < 0 || newHeadY >= ROWSY)
{
  game_over = true;
  return;
}

for (int i = 0; i < snake.length; i++)
{
  if (snake.segments[i].x == newHeadX && snake.segments[i].y == newHeadY)
  {
    game_over = true;
    return;
  }
}
```
these if statements are used to check for collisions with the game border and the segments of the snake itself

after this the code starts a big if statement for when an apple is eaten. in this if statement we have several important parts
```cpp
for (int i = snake.length; i > 0; i--)
  {
    snake.segments[i] = snake.segments[i - 1];
  }
```
this loop is used to set every segment to the segment in front of it when the snake gets an apple

```cpp
for (int i = 0; i < snake.length; i++)
      {
        if (snake.segments[i].x == apple.x && snake.segments[i].y == apple.y)
        {
          validPosition = false;
          break;
        }
      }
```
this loop checks the x and y positions of a newly generated apple with all segments of the snake, when the apple get created on a spot thats already in use, the boolean validPosition gets set to false and the proces of creating a new apple restarts.

### void readSensors()
this function is used to get sensor data from the joystick to give directions to the snake.
```cpp
if (vert < DOWNTHRES && snake.direction_y != -1)
  {
    snake.direction_x = 0;
    snake.direction_y = 1;
    totaldown++;
  }
```
in this code snippet you can see how the input from the joystick is handled. the smaller than 1000 is a countermeasure for stick drift. it ensures the snake doesnt move without being told to do so. it also counts the total times the function is called, this is used to display statistics at the end of the game

### void gameOverScreen()
this function is used to display a message when the game stops, it displays score and a big game over.

### void reset()
```cpp
snakeInit();
moveTime = millis();
```
this function updates the moveTime to the current time with millis(). this is used so the game knows when it needs to move the snake.

### void httpreq()
The httpreq function sends the snake’s movement statistics to a server using an HTTPS POST request. It first creates WiFi and HTTPS clients, then prepares a JSON object containing the number of times the snake moved up, down, left, and right. This JSON is converted into a string and sent over a secute HTTPS connection to the server. The function also prints the JSON to the serial monitor for debugging.

```cpp
HTTPClient httpClient;
httpClient.begin(client, url);
```
this bit of code is used to create a httpclient. this is then used to link a url to send the httprequest to.

```cpp
StaticJsonDocument<200> doc;
doc["totalup"] = totalup;
doc["totaldown"] = totaldown;
doc["totalleft"] = totalleft;
doc["totalright"] = totalright;
```
this bit of code creates a json document called doc. then it adds the totals to the json file.

```cpp
String jsonString;
serializeJson(doc, jsonString);
```
a string is created called jsonString. ater this the serialize Json puts the information from the doc into this string.
by doing this it makes it easier for the API to read.

```cpp
httpcode = httpClient.POST(jsonString);
```
this last bit of code sends the jsonString to the webpage(url).

### void startGame()
The startGame function initializes a new game by sending an HTTPS POST request to a server which in turn gets a game ID from a database. It also retrieves the server's response. These values are stored in player_id and game_id for use in the game. for more information on the code, see above(httpsreq)

### void webserver()
The webserver function listens for incoming connections on port 80. When a client connects, it reads the request and checks if the client has requested a specific endpoint (like "GET /debug"). Based on the request, the server either handles the request or responds with the corresponding information.

```cpp
WiFiClient client = server.available();
```
this code snippet checks if the server has a connection

```cpp
  if (client.available()) {
    char c = client.read();
    request += c;
    if (c == '\n') break;
  }
```
this part of the code puts the http request into a string named request.

```cpp
if (request.indexOf("GET /debug") >= 0) {
  debug();
}
```
the if statement checks if the request string contains a certain word or command and if it does it starts the debug
function

### void debug
The debug function is used for debugging purposes. It displays information on the OLED screen about the joystick's movements and button presses. It also provides visual feedback, guiding the user through various steps (e.g., pressing buttons, moving the joystick in different directions). After every action, it waits for user input before proceeding to the next step.

```cpp
while(digitalRead(BUTTON_1_PIN)){
  display.fillScreen(ILI9341_WHITE);
  display.display();
  delay(20);
}
```
this fills the entire display, this way you can see if a pixel is broken

```cpp
while (vert < UPTHRES){
  vert = analogRead(VERT_PIN);
  display.setCursor(0, 0);
  display.println("joystick omhoog");
  display.display();
}
```
this checks if the joystick can move upwards. this loop is copied for all directions

```cpp
while(digitalRead(BUTTON_1_PIN)){
  display.setCursor(0, 0);
  display.println("press button when");
  display.println("buzzer sounds");
  display.display();
  tone(BUZZER_PIN, 1000, 100);
}
```
this loop plays a sound on the buzzer, after this the user needs to press the button to continue.
