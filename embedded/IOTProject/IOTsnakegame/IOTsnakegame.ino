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
#define SEL_PIN 10

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

// struct for creating snakesegments in another struct
struct SnakeSegment
{
  int x;
  int y;
};

// struct for keeping information on the snake
struct Snake
{
  SnakeSegment segments[100];
  int length;
  int direction_x;
  int direction_y;
};

// struct for keeping information about the apple
struct Apple
{
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

// wifi credentials
// const char* ssid = "iotroam";
// const char* password = "xYEa1WO94W";
// const char* url = "";

// wifi credentials
const char *ssid = "Lan solo";
const char *password = "Zegikniet1";
const char *url = "http://192.168.178.61/api/post.php";

// initialization of the display
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

void snakeInit();
void createGame();
void drawSnake();
int readSensors();
void gameOverScreen();
void reset();
void httpreq(int horz, int vert);

void setup()
{
  Serial.begin(115200);

  // start wifi and i2c
  WiFi.begin(ssid, password);
  Wire.begin(SDA_PIN, SCL_PIN);

  // set pins for buttons
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  // set pins for joystick
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  // set pin for buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // start connection with display and check if i2c connection works
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED not found");
    while (true)
      ;
  }

  // initialize important things for display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  //initialize snake
  snakeInit();
}

/// @brief Initializes the snake game by resetting game variables.
/// This function sets the initial values for the snake game
void snakeInit()
{
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

/// @brief puts the elements needed for the game on the display.
/// This function clears the screen and then draws the initial apple and the snake
/// on the display using their x and y positions.
void createGame()
{
  display.clearDisplay();

  // converts apple x and y position to usable positions for the display
  int applex = (apple.x * BLOCKSIZE);
  int appley = (apple.y * BLOCKSIZE);

  // draws apples as a square on the display
  display.fillRect(applex, appley, BLOCKSIZE, BLOCKSIZE, WHITE);

  // loop through the snake segments and convert and fill them the same way as the apple
  for (int i = 0; i < snake.length; i++)
  {
    int x = snake.segments[i].x * BLOCKSIZE;
    int y = snake.segments[i].y * BLOCKSIZE;
    display.fillRect(x, y, BLOCKSIZE, BLOCKSIZE, SSD1306_WHITE);
  }

  // display everything on the screen
  display.display();
}

/// @brief Moves the snake forward and checks for collisions.
/// This function updates the snake's position, handles apple eating,
/// and checks for collisions with the walls or the snake's own segments.
void drawSnake()
{
  //if statement for when the snake isnt moving
  if (snake.direction_x == 0 && snake.direction_y == 0)
  {
    return;
  }

  // calculations for the new heads position
  int newHeadX = snake.segments[0].x + snake.direction_x;
  int newHeadY = snake.segments[0].y + snake.direction_y;

  // check if the head is outside the given game size
  if (newHeadX < 0 || newHeadX >= ROWSX || newHeadY < 0 || newHeadY >= ROWSY)
  {
    game_over = true;
    return;
  }

  // check if the snake hits its own segments
  for (int i = 0; i < snake.length; i++)
  {
    if (snake.segments[i].x == newHeadX && snake.segments[i].y == newHeadY)
    {
      game_over = true;
      return;
    }
  }

  // boolean for confirming if the snake eats an apple
  bool ateApple = (newHeadX == apple.x && newHeadY == apple.y);

  // if statement for when the snake does eat the apple
  if (ateApple)
  { 
    // loop to move segments forward after eating apple to make it longer
    for (int i = snake.length; i > 0; i--)
    {
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
    while (!validPosition)
    {
      // new x and y for apple
      apple.x = random(0, ROWSX);
      apple.y = random(0, ROWSY);
      validPosition = true;

      // for loop to check if the apple is put in a valid position (not in the snake segments)
      for (int i = 0; i < snake.length; i++)
      {
        if (snake.segments[i].x == apple.x && snake.segments[i].y == apple.y)
        {
          validPosition = false;
          break;
        }
      }
    }
    // not used right now
    // tone(BUZZER_PIN, 1000, 100);
  }
  else
  // if the snake doesnt eat an apple, move it forward
  {
    for (int i = snake.length - 1; i > 0; i--)
    {
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
void readSensors()
{

  // variables for the reading of the joystick
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);

  // not used
  // bool selPressed = digitalRead(SEL_PIN) == LOW;
  // bool button1 = !digitalRead(BUTTON_1_PIN);
  // bool button2 = !digitalRead(BUTTON_2_PIN);


  // if statement to check if the joystick is going down
  if (vert < 1000 && snake.direction_y != -1)
  {
    // updates direction
    snake.direction_x = 0;
    snake.direction_y = 1;
    // updates the total amount of times in the game the player has gone down
    totaldown++;
  }
  // if statement to check if the joystick is going up
  else if (vert > 3000 && snake.direction_y != 1)
  {
    // updates direction
    snake.direction_x = 0;
    snake.direction_y = -1;
    // updates the total amount of times in the game the player has gone up
    totalup++;
  }

  // if statement to check if the joystick is going left
  if (horz < 1000 && snake.direction_x != 1)
  {
    // updates direction
    snake.direction_x = -1;
    snake.direction_y = 0;
    // updates the total amount of times in the game the player has gone left
    totalleft++;
  }
  // if statement to check if the joystick is going right
  else if (horz > 3000 && snake.direction_x != -1)
  {
    // updates direction
    snake.direction_x = 1;
    snake.direction_y = 0;
    // updates the total amount of times in the game the player has gone right
    totalright++;
  }
}


void gameOverScreen()
{
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

void reset()
{
  snakeInit();
  moveTime = millis();
}

void httpreq(int totalup, int totaldown, int totalleft, int totalright)
{
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

void loop()
{
  if (!game_over)
  {
    readSensors();

    if (millis() - moveTime >= moveSpeed)
    {
      drawSnake();
      moveTime = millis();
    }

    createGame();
  }
  else
  {
    gameOverScreen();

    if (!digitalRead(BUTTON_1_PIN))
    {
      reset();
      delay(500);
    }
  }
}
