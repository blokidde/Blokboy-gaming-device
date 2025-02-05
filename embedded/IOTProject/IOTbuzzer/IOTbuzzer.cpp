#define BUZZER_PIN 46

void setup() {
  Serial.begin(115200);
}

void loop() {
  tone(BUZZER_PIN, 150, 250);
}