#define BUTTON1_PIN 17
#define BUTTON2_PIN 18

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  int button1 = analogRead(BUTTON1_PIN);
  int button2 = analogRead(BUTTON2_PIN);
  Serial.println(button1);
  Serial.println(button2);
  Serial.println(" ");
}