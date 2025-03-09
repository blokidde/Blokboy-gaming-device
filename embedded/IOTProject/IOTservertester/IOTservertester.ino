#include <WiFiManager.h>
#include <WiFi.h>

WiFiServer server(80);

void setup() {
    Serial.begin(115200);

    WiFiManager wifiManager;

    if (!wifiManager.autoConnect("ESP32-Setup")) {
        Serial.println("Failed to connect, restarting...");
        delay(3000);
        ESP.restart();
    }

    Serial.println("Connected to WiFi!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    server.begin();
    Serial.println("Webserver started");
}

void loop() {
    WiFiClient client = server.available();

    if (client) {
        Serial.println("New Client connected!");
        String request = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                request += c;
                if (c == '\n') break;
            }
        }

        Serial.println("Client Request: ");
        Serial.println(request);
        client.stop();
        Serial.println("Client disconnected.");
    }
}
