/*
 * Description: IOTProject based on the handheld gamedevice blueprint.
 * Author:  Jurriaan Egmond
 * Date:    03/02/2025
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// -- Pas deze pinnen eventueel aan als je board dat vereist --
#define TFT_DC    9
#define TFT_CS    10
#define TFT_RST   46     // Check of GPIO46 op jouw board bruikbaar is
#define TFT_MOSI  11
#define TFT_SCK   12
#define TFT_MISO  13
#define TFT_LED   14     // Backlight pin (optioneel)

// Maak een ILI9341 object aan voor (hardware) SPI:
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ILI9341 test...");

  // Zet de backlight aan (als je deze direct via een GPIO wilt schakelen).
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH); // backlight aan

  // Start de SPI-hardware op met de door jou gekozen pins
  // Volgorde: SPI.begin(SCK, MISO, MOSI, SS)
  SPI.begin(TFT_SCK, TFT_MISO, TFT_MOSI, TFT_CS);

  // Initialiseer het display
  tft.begin();

  // Teksttest
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(2);
}

void loop() {
  tft.println("hello world")
}
