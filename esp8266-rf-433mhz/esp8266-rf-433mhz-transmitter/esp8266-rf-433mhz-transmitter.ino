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

#define TX_PIN 11 // arduino pin 11

RCSwitch rc = RCSwitch();

void setup_rcswitch() {
  rc.disableReceive();
  rc.enableTransmit(TX_PIN);
}

void loop_rcswitch() {
  rc.send(5, 24);
  Serial.println("Sent");
  delay(2000);
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
