#define VERT_PIN 16
#define HORZ_PIN 17
#define SEL_PIN  10

void setup() {
  Serial.begin(115200);
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  //pinMode(SEL_PIN, INPUT_PULLUP);
}

void loop() {
  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);
  bool selPressed = digitalRead(SEL_PIN) == LOW;
  Serial.println(vert);
  Serial.println(horz);
  Serial.println(" ");
  delay(100);
}