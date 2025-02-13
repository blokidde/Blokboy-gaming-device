#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "Lan solo";
const char* password = "Zegikniet1";
const char* url = "http://192.168.178.61/api/post.php";

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  WiFiClient client;
  HTTPClient httpClient;
  
  httpClient.begin(client, url);
  
  httpClient.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> doc;
  doc["username"] = "jurriaan4";
  String jsonString;
  serializeJson(doc, jsonString);
  
  Serial.print("Verstuurde JSON: ");
  Serial.println(jsonString);
  
  int httpCode = httpClient.POST(jsonString);

  if(httpCode > 0) {
    Serial.print("HTTP Response Code: ");
    Serial.println(httpCode);
    String payload = httpClient.getString();
    Serial.println("Server respons:");
    Serial.println(payload);
  } else {
    Serial.print("Fout bij het versturen: ");
    Serial.println(httpClient.errorToString(httpCode));
  }
  
  httpClient.end();
  
  delay(5000);
}