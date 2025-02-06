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

struct snake {
  int coordinates_x;
  int coordinates_y;
  int length;
  int direction_x;
  int direction_y;
};

struct apple {
  int x;
  int y;
};

snake snake[MAX_LENGTH];

int score = 0;

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true)
      ;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);
  bool selPressed = digitalRead(SEL_PIN) == LOW;

  bool button1 = !digitalRead(BUTTON_1_PIN);
  bool button2 = !digitalRead(BUTTON_2_PIN);


  display.clearDisplay();
  display.setCursor(0, 0);

  if (vert < 1900){
    display.println("left");
    display.display();
  } else if (vert > 2100){
    display.println("right");
    display.display();
  }

  if (horz < 1900){
    display.println("down");
    display.display();
  } else if (horz > 2100){
    display.println("up");
    display.display();
  }

  if (button1){
    display.println("button 1 pressed");
    display.display();
  } else if (button2){
    display.println("button 2 pressed");
    display.display();
  }

  Serial.println(vert);
  Serial.println(horz);
}
