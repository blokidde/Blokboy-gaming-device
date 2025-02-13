#include <WiFiManager.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

WiFiManager wm;

void setup() {
  Serial.begin(115200);
  if (!wm.autoConnect("ESP32-Config")) {
    Serial.println("no connection");
    ESP.restart();
  }
  StaticJsonDocument<200> doc;
  doc["player_id"] = 1;
  doc["score"] = 50;
  doc["game_id"] = 2;

  String jsonString;
  serializeJson(doc, jsonString);

  Serial.println(jsonString);

  HTTPClient http;

  http.begin("http://192.168.128.1/api/get.php");
  http.addHeader("Content-Type", "application/json");

  int httpresponse = http.POST(jsonString);
  Serial.println("HTTP Response Code: ");
  Serial.println(httpresponse);

  String response = http.getString();
  Serial.println("Server antwoord: ");
  Serial.println(response);

  http.end();
}

void loop() {
}
