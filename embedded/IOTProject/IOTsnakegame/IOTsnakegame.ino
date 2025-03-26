#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

// joystick pins
#define VERT_PIN 18
#define HORZ_PIN 17
#define SEL_PIN 11

// joystick constants
#define UPTHRES 3500
#define DOWNTHRES 500
#define LEFTTHRES 500
#define RIGHTTHRES 3500

// ili9341 pins and defines
#define TFT_SPI_FREQUENCY 10000000
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  3
#define TFT_CLK  4
#define TFT_MOSI 5
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320

// button pins
#define BUTTON_1_PIN 6
#define BUTTON_2_PIN 7

// max lenght of the snake
#define MAX_LENGTH 100

// buzzer pin
#define BUZZER_PIN 1

// size of the game, display is 320 by 240, game has blocks size of 4
// so 240 and 320 divided by 4
#define BLOCKSIZE 4
#define ROWSX 60
#define ROWSY 80

// struct for creating snakesegments in another struct
struct SnakeSegment {
  int x;
  int y;
};

// struct for keeping information on the snake
struct Snake {
  SnakeSegment segments[100];
  int length;
  int direction_x;
  int direction_y;
};

// struct for keeping information about the apple
struct Apple {
  int x;
  int y;
};

Snake snake;
Apple apple;

bool game_over;

// variables for the game
int score = 0;
int totalleft;
int totalright;
int totalup;
int totaldown;

// variables needed for the game
unsigned long moveTime = 0;
const unsigned long moveSpeed = 200;

// variable for http request
int httpCode;

// variables for information about the game
int player_id = 0;
int game_id = 0;

WiFiServer server(80);

// wifi credentials school
// const char* ssid = "iotroam";
// const char* password = "xYEa1WO94W";
// const char* url = "http://145.92.189.65/api/insert.php";
// const char* starturl = "http://145.92.189.65/api/start_game.php";

// // // wifi credentials home
// const char *ssid = "Lan solo";
// const char *password = "Zegikniet1";
const char *url = "http://192.168.178.61/api/insert.php";
const char* starturl = "http://192.168.178.61/api/start_game.php";

// initialization of the display
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void snakeInit();
void createGame();
void drawSnake();
void readSensors();
void gameOverScreen();
void reset();
void httpreq(int game_id, int totalup, int totaldown, int totalleft, int totalright, int score);
void startGame();
void webserver();
void debug();

void setup() {
  Serial.begin(115200);

  //seeding the random generator with the time
  randomSeed(micros());

  // not used
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(250);
  //   Serial.print(".");
  // }

  WiFiManager wifiManager;
  // start wifi and i2c
  if (!wifiManager.autoConnect("ESP32-Setup")) {
    Serial.println("Failed to connect, restarting...");
    delay(3000);
    ESP.restart();
  }

  Serial.println("Connected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Webserver started");
  SPI.begin(TFT_CLK, -1, TFT_MOSI);
  display.begin();

  // set pins for buttons
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  // set pins for joystick
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  // set pin for buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // not used
  // start connection with display and check if i2c connection works
  // if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  //   Serial.println("OLED not found");
  //   while (true)
  //     ;
  // }

  // initialize important things for display
  //display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(ILI9341_WHITE);
  display.fillScreen(ILI9341_BLACK);

  //initialize snake
  snakeInit();
}

/// @brief Initializes the snake game by resetting game variables.
/// This function sets the initial values for the snake game
void snakeInit() {

  startGame();
  // set all the variables to 0 or false
  game_over = false;
  score = 0;
  totalup = 0;
  totaldown = 0;
  totalleft = 0;
  totalright = 0;

  // set length of initial snake
  snake.length = 1;

  // set first snake segments on random place
  snake.segments[0].x = random(0, ROWSX);
  snake.segments[0].y = random(0, ROWSY);

  // no movement when starting
  snake.direction_x = 0;
  snake.direction_y = 0;

  // set the first apple on a random x and y
  apple.x = random(0, ROWSX);
  apple.y = random(0, ROWSY);
}

/// @brief puts the elements needed for the game on the display.
/// This function clears the screen and then draws the initial apple and the snake
/// on the display using their x and y positions.
void createGame() {
  //display.clearDisplay();
  display.startWrite();
  // draw the border for the game
  display.drawRect(0, 0, 128, 32, ILI9341_WHITE);

  // converts apple x and y position to usable positions for the display
  int applex = (apple.x * BLOCKSIZE);
  int appley = (apple.y * BLOCKSIZE);

  // draws apples as a square on the display
  display.fillRect(applex, appley, BLOCKSIZE, BLOCKSIZE, ILI9341_WHITE);

  // loop through the snake segments and convert and fill them the same way as the apple
  for (int i = 0; i < snake.length; i++) {
    int x = snake.segments[i].x * BLOCKSIZE;
    int y = snake.segments[i].y * BLOCKSIZE;
    display.fillRect(x, y, BLOCKSIZE, BLOCKSIZE, ILI9341_WHITE);
  }
  display.endWrite();

  // display everything on the screen
  //display.display();
}

/// @brief Moves the snake forward and checks for collisions.
/// This function updates the snake's position, handles apple eating,
/// and checks for collisions with the walls or the snake's own segments.
void drawSnake() {
  //if statement for when the snake isnt moving
  if (snake.direction_x == 0 && snake.direction_y == 0) {
    return;
  }

  // count total amount the snake moves and which directions
  if (snake.direction_x == 1) {
    totalright++;
  } else if (snake.direction_x == -1) {
    totalleft++;
  } else if (snake.direction_y == 1) {
    totaldown++;
  } else if (snake.direction_y == -1) {
    totalup++;
  }

  // calculations for the new heads position
  int newHeadX = snake.segments[0].x + snake.direction_x;
  int newHeadY = snake.segments[0].y + snake.direction_y;

  // check if the head is outside the given game border
  if (newHeadX < 0 || newHeadX >= ROWSX || newHeadY < 0 || newHeadY >= ROWSY) {
    game_over = true;
    return;
  }

  // check if the snake hits its own segments
  for (int i = 0; i < snake.length; i++) {
    if (snake.segments[i].x == newHeadX && snake.segments[i].y == newHeadY) {
      game_over = true;
      return;
    }
  }

  // boolean for confirming if the snake eats an apple
  bool ateApple = (newHeadX == apple.x && newHeadY == apple.y);

  // if statement for when the snake does eat the apple
  if (ateApple) {
    // loop to move segments forward after eating apple to make it longer
    for (int i = snake.length; i > 0; i--) {
      snake.segments[i] = snake.segments[i - 1];
    }

    // set the position of the new head
    snake.segments[0].x = newHeadX;
    snake.segments[0].y = newHeadY;

    // adds length to the snake and to the score
    snake.length++;
    score++;

    bool validPosition = false;

    // loop to create new apple in random x and y position
    while (!validPosition) {
      // new x and y for apple
      apple.x = random(0, ROWSX);
      apple.y = random(0, ROWSY);
      validPosition = true;

      // for loop to check if the apple is put in a valid position (not in the snake segments)
      for (int i = 0; i < snake.length; i++) {
        if (snake.segments[i].x == apple.x && snake.segments[i].y == apple.y) {
          validPosition = false;
          break;
        }
      }
    }
    // not used right now
    // tone(BUZZER_PIN, 1000, 100);
  } else
  // if the snake doesnt eat an apple, move it forward
  {
    for (int i = snake.length - 1; i > 0; i--) {
      // update the segment to the segments infront of it
      snake.segments[i] = snake.segments[i - 1];
    }

    // set new head x and y
    snake.segments[0].x = newHeadX;
    snake.segments[0].y = newHeadY;
  }
}

/// @brief reads the sensors and updates the direction of the snake
/// this function converts the analog inputs from the sensors to usable
/// data the game can use to go towards any direction
void readSensors() {

  // variables for the reading of the joystick
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);

  // not used
  // bool selPressed = digitalRead(SEL_PIN) == LOW;
  // bool button1 = !digitalRead(BUTTON_1_PIN);
  // bool button2 = !digitalRead(BUTTON_2_PIN);


  // if statement to check if the joystick is going down
  if (vert < DOWNTHRES && snake.direction_y != -1) {
    // updates direction
    snake.direction_x = 0;
    snake.direction_y = 1;
  }
  // if statement to check if the joystick is going up
  else if (vert > UPTHRES && snake.direction_y != 1) {
    // updates direction
    snake.direction_x = 0;
    snake.direction_y = -1;
  }

  // if statement to check if the joystick is going left
  if (horz < LEFTTHRES && snake.direction_x != 1) {
    // updates direction
    snake.direction_x = -1;
    snake.direction_y = 0;
  }
  // if statement to check if the joystick is going right
  else if (horz > RIGHTTHRES && snake.direction_x != -1) {
    // updates direction
    snake.direction_x = 1;
    snake.direction_y = 0;
  }
}

/// @brief puts a big game over on the display
void gameOverScreen() {
  display.startWrite();
  //display.clearDisplay();
  // size of the text
  display.setTextSize(2);
  // startpoint for the text
  display.setCursor(10, 0);
  display.print("Game Over");
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Score: ");
  display.print(score);
  display.endWrite();
  //display.display();
}

/// @brief this resets the game
void reset() {
  snakeInit();
  // sets start time for momvement time for the next game
  moveTime = millis();
}


/// @brief Sends a JSON HTTP request with movement statistics.
/// This function sends a HTTP POST request containing the total movement
/// stats of the snake during a game
/// @param game_id ID created by database, used as foreign keys for.
/// @param totalup The number of times the snake moved up.
/// @param totaldown The number of times the snake moved down.
/// @param totalleft The number of times the snake moved left.
/// @param totalright The number of times the snake moved right.
/// @param score The amount of points gotten in a game.
void httpreq(int game_id, int totalup, int totaldown, int totalleft, int totalright, int score) {

  // create clients for wifi and http
  WiFiClient client;
  HTTPClient httpClient;

  // initialize http client with url
  httpClient.begin(client, url);

  // set the content to send to json
  httpClient.addHeader("Content-Type", "application/json");

  // create json document with necessary information
  StaticJsonDocument<200> doc;
  doc["game_id"] = game_id;
  doc["totalup"] = totalup;
  doc["totaldown"] = totaldown;
  doc["totalleft"] = totalleft;
  doc["totalright"] = totalright;
  doc["score_value"] = score;
  // create string called jsonstring
  String jsonString;
  // convert the json (doc) to a string (jsonstring)
  serializeJson(doc, jsonString);

  Serial.print("Verstuurde JSON: ");
  Serial.println(jsonString);

  // send the json string
  httpCode = httpClient.POST(jsonString);

  if (httpCode > 0) {
    // print response code from http POST
    Serial.println(httpCode);
  } else {
    Serial.print("POST failed: ");
    Serial.println(httpCode);
  }
}

void startGame() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    return;
  }

  WiFiClient client;
  HTTPClient http;
  http.begin(client, starturl);
  http.addHeader("Content-Type", "application/json");

  // Creëer JSON payload
  StaticJsonDocument<200> doc;
  doc["generate"] = 1;
  String jsonString;
  serializeJson(doc, jsonString);

  // Verstuur HTTP POST
  int httpResponseCode = http.POST(jsonString);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("Response from startGame: ");
    Serial.println(response);

    // JSON-resultaat parsen
    StaticJsonDocument<200> responseDoc;
    DeserializationError error = deserializeJson(responseDoc, response);
    if (!error && responseDoc["status"] == "success") {
      // player_id en game_id uitlezen
      player_id = responseDoc["player_id"] | 0;
      game_id = responseDoc["game_id"] | 0;
    } else {
      Serial.println("Failed to parse JSON or status != success.");
    }
  } else {
    Serial.print("POST failed, error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void webserver() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client connected!");
    String request = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\n') break;
      }
    }

    if (request.indexOf("GET /debug") >= 0) {
      debug();
    }
    Serial.println("Client Request: ");
    Serial.println(request);
    client.stop();
    Serial.println("Client disconnected.");
  }
}

void debug(){
  display.startWrite();
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);
  //display.clearDisplay();
  display.setCursor(0, 0);
  display.println("starting debug");
  //display.display();
  delay(5000);
  //display.clearDisplay();
  display.setCursor(0, 0);
  display.println("press button to continue");
  //display.display();
  delay(5000);
  display.fillRect(0, 0, display.width(), display.height(), ILI9341_WHITE);
  while(digitalRead(BUTTON_1_PIN)){
    //display.display();
    delay(20);
  }
  display.fillRect(0, 0, display.width(), display.height(), ILI9341_BLACK);
  //display.clearDisplay();
  while (vert < UPTHRES){
    vert = analogRead(VERT_PIN);
    display.setCursor(0, 0);
    display.println("joystick omhoog");
    //display.display();
  }
  //display.clearDisplay();
  while (vert > DOWNTHRES){
    vert = analogRead(VERT_PIN);
    display.setCursor(0, 0);
    display.println("joystick omlaag");
    //display.display();
  }
  //display.clearDisplay();
  while (horz > LEFTTHRES){
    horz = analogRead(HORZ_PIN);
    display.setCursor(0, 0);
    display.println("joystick links");
    //display.display();
  }
  //display.clearDisplay();
  while (horz < RIGHTTHRES){
    horz = analogRead(HORZ_PIN);
    display.setCursor(0, 0);
    display.println("joystick rechts");
    //display.display();
  }
  //display.clearDisplay();
  while(digitalRead(BUTTON_1_PIN)){
    display.setCursor(0, 0);
    display.println("press button when");
    display.println("buzzer sounds");
    //display.display();
    tone(BUZZER_PIN, 1000, 100);
  }
  display.endWrite();
  delay(1000);
}

void loop() {
  if (!game_over) {
    readSensors();
    httpCode = 0;
    if (millis() - moveTime >= moveSpeed) {
      drawSnake();
      moveTime = millis();
    }

    createGame();
  } else {
    gameOverScreen();
    // used for debugging
    //Serial.printf("\n%d %d %d %d \n", totalup, totaldown, totalleft, totalright);
    if (httpCode != 200) {
      httpreq(game_id, totalup, totaldown, totalleft, totalright, score);
    }
    webserver();
    if (!digitalRead(BUTTON_1_PIN)) {
      reset();
      delay(500);
    }
  }
}
