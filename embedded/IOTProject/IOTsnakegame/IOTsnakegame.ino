#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

void snakeInit();
void createGame();
void drawSnake();
void readSensors();

void setup() {
  Serial.begin(115200);
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

void snakeInit() {
  game_over = false;
  score = 0;

  snake.length = 1;
  snake.segments[0].x = ROWSX / 2;
  snake.direction_x = 0;
  snake.direction_y = 0;

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

}

void readSensors(){
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);
  // not used
  //bool selPressed = digitalRead(SEL_PIN) == LOW;

  bool button1 = !digitalRead(BUTTON_1_PIN);
  bool button2 = !digitalRead(BUTTON_2_PIN);

  if (vert < 1900){
    Serial.println("down");
  } else if (vert > 2100){
    Serial.println("up");
  }

  if (horz < 1900){
    Serial.println("left");
  } else if (horz > 2100){
    Serial.println("right");
  }

  if (button1){
    tone(BUZZER_PIN, 500, 10);
    Serial.println("buzzer");
  } else if (button2){
    Serial.println("buttn2");
  } else {
    tone(BUZZER_PIN, 0, 0);
  }
}

void gameOverScreen(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 10);
  display.print("Game Over");
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.print("Score: ");
  display.print(score);
  display.display();
}

void loop() {
  readSensors();
  createGame();
}
