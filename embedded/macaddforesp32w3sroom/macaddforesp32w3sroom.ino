#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Lan solo";
const char* password = "Zegikniet1";

void setup() {
  // Initialize the Serial-connection on a speed of 115200 b/s
  Serial.begin(115200);

  // Your WeMos tries to connect to your Wi-fi network
  WiFi.begin(ssid, password);

  // Keep the while-statement alive as long as we are NOT connected
  // to the Wi-fi network.
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("not connected to wifi ");
    delay(1000);
  }

  Serial.println("connected");
}

void loop() {
  // Initialize a wi-fi client & http client
  WiFiClient client;
  HTTPClient httpClient;

  // Set the URL of where the call should be made to.
  httpClient.begin(client, "http://192.168.178.61/api/get.php");

  // Make the GET-request, this returns the HTTP-code.
  int httpCode = httpClient.GET();

  // Check if the response is fine.
  if(httpCode == HTTP_CODE_OK) { // HTTP_CODE_OK == 200
    // Print the body of the GET-request response.
    String payload = httpClient.getString();
    Serial.println(payload);
  } else {
    Serial.println("Unable to connect :(");
  }

  delay(5000);
}