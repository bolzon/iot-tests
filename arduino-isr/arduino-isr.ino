const byte interruptPin = 2; // interrupt 0

void setup() {
  pinMode(interruptPin, INPUT PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), serialPrint, CHANGE);
}

void serialPrint() {
  Serial.println(digitalRead(interruptPin));
}