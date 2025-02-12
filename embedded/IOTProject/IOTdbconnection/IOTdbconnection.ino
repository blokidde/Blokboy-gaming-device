#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);

  StaticJsonDocument<200> doc;
  doc["player_id"] = 2;
  doc["score"] = 5;
  doc["game_id"] = 2

  String jsonString;
  serializeJson(doc, jsonString);

  Serial.println(jsonString);
}

void loop() {

}
