const byte interruptPin = 2; // interrupt 0

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), serialPrint, CHANGE);
}

void loop() {
}

void serialPrint() {
  Serial.print(digitalRead(interruptPin));
}
