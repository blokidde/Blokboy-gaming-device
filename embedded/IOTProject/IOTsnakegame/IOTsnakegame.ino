#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#define VERT_PIN 18
#define HORZ_PIN 17
#define SEL_PIN  10

#define SDA_PIN 15
#define SCL_PIN 16
#define OLED_RESET -1
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

#define BUTTON_1_PIN 4
#define BUTTON_2_PIN 5

#define MAX_LENGTH 100

#define BUZZER_PIN 1

#define ROWSX 32
#define ROWSY 8
#define BLOCKSIZE 4

struct SnakeSegment {
  int x;
  int y;
};

struct Snake {
  SnakeSegment segments[100];
  int length;
  int direction_x;
  int direction_y;
};

struct Apple {
  int x;
  int y;
};

Snake snake;
Apple apple;

bool game_over;

int score = 0;

int totalleft;
int totalright;
int totalup;
int totaldown;

unsigned long moveTime = 0;
const unsigned long moveSpeed = 200;

// const char* ssid = "iotroam";
// const char* password = "xYEa1WO94W";
// const char* url = "";

const char* ssid = "Lan solo";
const char* password = "Zegikniet1";
const char* url = "http://192.168.178.61/api/post.php";


Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

void snakeInit();
void createGame();
void drawSnake();
int readSensors();
void gameOverScreen();
void reset();
void httpreq(int horz, int vert);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true)
      ;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  snakeInit();
}



/// @brief Initializes the snake game by resetting game variables.
// This function sets the initial values for the snake game
void snakeInit() {
  // set all the variables to 0 or false
  game_over = false;
  score = 0;
  totalup = 0;
  totaldown = 0;
  totalleft = 0;
  totalright = 0;

  // set all elements of the snake to its startign position
  snake.length = 1;
  snake.segments[0].x = ROWSX / 2;
  snake.direction_x = 0;
  snake.direction_y = 0;

  // set the first apple on a random x and y
  apple.x = random(0, ROWSX);
  apple.y = random(0, ROWSY);
}

void createGame(){
  display.clearDisplay();

  int applex = (apple.x * BLOCKSIZE);
  int appley = (apple.y * BLOCKSIZE);
  display.fillRect(applex, appley, BLOCKSIZE, BLOCKSIZE, WHITE);

  for (int i = 0; i < snake.length; i++) {
    int x = snake.segments[i].x * BLOCKSIZE;
    int y = snake.segments[i].y * BLOCKSIZE;
    display.fillRect(x, y, BLOCKSIZE, BLOCKSIZE, SSD1306_WHITE);
  }

  display.display();
}

void drawSnake(){
if (snake.direction_x == 0 && snake.direction_y == 0) {
    return;
  }
  
  int newHeadX = snake.segments[0].x + snake.direction_x;
  int newHeadY = snake.segments[0].y + snake.direction_y;
  
  if (newHeadX < 0 || newHeadX >= ROWSX || newHeadY < 0 || newHeadY >= ROWSY) {
    game_over = true;
    return;
  }
  
  for (int i = 0; i < snake.length; i++) {
    if (snake.segments[i].x == newHeadX && snake.segments[i].y == newHeadY) {
      game_over = true;
      return;
    }
  }
  
  bool ateApple = (newHeadX == apple.x && newHeadY == apple.y);
  
  if (ateApple) {
    for (int i = snake.length; i > 0; i--) {
      snake.segments[i] = snake.segments[i - 1];
    }
    snake.segments[0].x = newHeadX;
    snake.segments[0].y = newHeadY;
    snake.length++;
    score++;
    
    bool valid = false;
    while (!valid) {
      apple.x = random(0, ROWSX);
      apple.y = random(0, ROWSY);
      valid = true;
      for (int i = 0; i < snake.length; i++) {
        if (snake.segments[i].x == apple.x && snake.segments[i].y == apple.y) {
          valid = false;
          break;
        }
      }
    }
    tone(BUZZER_PIN, 1000, 100);
  } else {
    for (int i = snake.length - 1; i > 0; i--) {
      snake.segments[i] = snake.segments[i - 1];
    }
    snake.segments[0].x = newHeadX;
    snake.segments[0].y = newHeadY;
  }
}

void readSensors(){
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);

  // not used
  //bool selPressed = digitalRead(SEL_PIN) == LOW;
  // bool button1 = !digitalRead(BUTTON_1_PIN);
  // bool button2 = !digitalRead(BUTTON_2_PIN);

  if (vert < 1000 && snake.direction_y != -1){
    snake.direction_x = 0;
    snake.direction_y = 1;
    totaldown++;
  } else if (vert > 3000 && snake.direction_y != 1){
    snake.direction_x = 0;
    snake.direction_y = -1;
    totalup++;
  }

  if (horz < 1000 && snake.direction_x != 1){
    snake.direction_x = -1;
    snake.direction_y = 0;
    totalleft++;
  } else if (horz > 3000 && snake.direction_x != -1){
    snake.direction_x = 1;
    snake.direction_y = 0;
    totalright++;
  }

}

void gameOverScreen(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 0);
  display.print("Game Over");
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Score: ");
  display.print(score);
  display.display();
}

void reset(){
  snakeInit();
  moveTime = millis();
}

void httpreq(int totalup, int totaldown, int totalleft, int totalright){
  WiFiClient client;
  HTTPClient httpClient;

  httpClient.begin(client, url);
  httpClient.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> doc;
  doc["totalup"] = totalup;
  doc["totaldown"] = totaldown;
  doc["totalleft"] = totalleft;
  doc["totalright"] = totalright;
  String jsonString;
  serializeJson(doc, jsonString);
  
  Serial.print("Verstuurde JSON: ");
  Serial.println(jsonString);
  
  httpcode = httpClient.POST(jsonString);
}

void loop() {
  if (!game_over) {
    readSensors();
    
    if (millis() - moveTime >= moveSpeed) {
      drawSnake();
      moveTime = millis();
    }
    
    createGame();
  } else {
    gameOverScreen();
    
    if (!digitalRead(BUTTON_1_PIN)) {
      reset();
      delay(500);
    }
  }
}
