#include <RCSwitch.h>

// nodemcu pins

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15

#define TX_PIN 11
#define RX_PIN 10

RCSwitch rc = RCSwitch();

int count = 0;

void setup_rcswitch() {
  rc.enableReceive(RX_PIN);
  rc.enableTransmit(TX_PIN);
}

void loop_rcswitch() {
  if (rc.available()) {
    Serial.print(rc.getReceivedValue());
    Serial.print(" / ");
    Serial.print(rc.getReceivedBitlength());
    Serial.print("bit ");
    Serial.print("Protocolo: ");
    Serial.println(rc.getReceivedProtocol());
    rc.resetAvailable();
  }

  if (++count > 10000) {
    rc.send(5, 24);
    Serial.println("Sent");
    count = 0;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.print("Initializing... ");
  setup_rcswitch();
  Serial.println("OK");
}

void loop() {
  loop_rcswitch();
}
