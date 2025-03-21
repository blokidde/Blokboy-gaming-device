#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC    9
#define TFT_CS    10
#define TFT_RST   46
#define TFT_MOSI  11
#define TFT_SCK   12
#define TFT_MISO  13
#define TFT_LED   14

Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ILI9341 test...");

  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  SPI.begin(TFT_SCK, TFT_MISO, TFT_MOSI, TFT_CS);
  display.begin();
  display.fillScreen(ILI9341_BLACK);
}

void loop() {
  display.setCursor(0, 0);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(2);
  display.println("hello world");
}