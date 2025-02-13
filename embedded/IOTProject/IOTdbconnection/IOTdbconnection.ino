#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

const char* ssid = "iotroam";
const char* password = "xYEa1WO94W";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  StaticJsonDocument<200> doc;
  doc["player_id"] = 2;
  doc["score"] = 50;
  doc["game_id"] = 2;
  String jsonString;
  serializeJson(doc, jsonString);
  Serial.print("Verzonden JSON: ");
  Serial.println(jsonString);

  WiFiClient client;

  HTTPClient http;

  http.begin(client, "http://145.3.253.18/api/get.php");
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(jsonString);
  
  if(httpResponseCode > 0) {
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.println(http.errorToString(httpResponseCode));
  }
  http.end();
}

void loop() {
}
