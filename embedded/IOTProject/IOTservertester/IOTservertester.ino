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

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        client.println("<!DOCTYPE html><html><body>");
        client.println("<h1>ESP32 Webserver met WiFiManager</h1>");
        client.println("<p>ESP32 is verbonden met WiFi!</p>");
        client.println("</body></html>");
        client.println();

        client.stop();
        Serial.println("Client disconnected.");
    }
}
