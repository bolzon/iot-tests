const int rx_pin = 12; // uno r3

void setup() {
    Serial.begin(9600);
    pinMode(rx_pin, INPUT);
}

void loop() {
    Serial.println(digitalRead(rx_pin));
}