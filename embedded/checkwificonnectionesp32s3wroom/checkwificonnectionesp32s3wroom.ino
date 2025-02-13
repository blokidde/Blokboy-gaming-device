#include <WiFi.h>

const char* ssid = "iotroam";
const char* password = "xYEa1WO94W";

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi is still connected.");
    } else {
        Serial.println("WiFi disconnected!");
    }
    delay(5000); // Check every 5 seconds
}
