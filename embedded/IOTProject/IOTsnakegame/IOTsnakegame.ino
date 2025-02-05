#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define VERT_PIN 16
#define HORZ_PIN 17
#define SEL_PIN  10

#define SDA_PIN 7
#define SCL_PIN 15

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

#define MAX_LENGTH 100

struct snake {
  int coordinates_x;
  int coordinates_y;
  int length;
  int direction_x;
  int direction_y;
}

struct apple {
  int x;
  int y;
}

snake snake[MAX_LENGTH];

int score = 0;

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);
  bool selPressed = digitalRead(SEL_PIN) == LOW;

  display.clearDisplay();
  display.setCursor(0, 0);

  if (vert < 2000){
    display.Println("left")
  } else
}
