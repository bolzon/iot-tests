const byte code[] = {
    0, 1
};

const int tx_pin = 12; // uno r3
const size_t wave_period = 312; // uS
const size_t pause_period = 9000; // uS
const size_t code_len = sizeof(code);

void setup() {
    pinMode(tx_pin, OUTPUT);
    digitalWrite(tx_pin, LOW);
}

void loop() {
    for (int i = 0; i < code_len - 1; i++) {
        digitalWrite(tx_pin, code[i]);
        delayMicroseconds(wave_period);
    }
    delayMicroseconds(pause_period);
}