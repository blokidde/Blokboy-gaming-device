#include <WiFiManager.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

WiFiManager wm;

void setup() {
    Serial.begin(115200);
    if (wm.autoConnect("ESP32-Config")){
      Serial.println("no connection");
      ESP.restart();
    }
    StaticJsonDocument<200> doc;
    doc["player_id"] = 1;
    doc["score"] = 5000;
    doc["game_id"] = 2;

    String jsonString;
    serializeJson(doc, jsonString);

    HTTPClient http;

    http.begin(server);
    http.addHeader("Content-Type", "application/json")

    Serial.println(jsonString);
}

void loop() {
}

