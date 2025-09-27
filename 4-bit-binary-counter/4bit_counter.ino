int ledPins[4] = {2, 3, 4, 5};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int count = 0; count < 16; count++) {
    for (int bit = 0; bit < 4; bit++) {
      int state = (count >> bit) & 1;
      digitalWrite(ledPins[bit], state);
    }
    delay(3000);
  }
}
