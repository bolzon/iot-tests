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

#define RX_PIN D1

RCSwitch rc = RCSwitch();

void setup_rcswitch() {
  rc.disableTransmit();
  rc.enableReceive(RX_PIN);
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
