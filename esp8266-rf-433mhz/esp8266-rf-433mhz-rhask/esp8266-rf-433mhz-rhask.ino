/*#include <RH_ASK.h>

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

#ifdef ESP8266
 #define TX_PIN D4
 #define RX_PIN D2
#else
 #define TX_PIN 11
 #define RX_PIN 10
#endif

RH_ASK driver(2000, 0, TX_PIN, 0); // speed (default 2000), rx pin, tx pin, ptt pin, ptt inverted

unsigned long last_sent = 0;
const unsigned long interval = 3000;

void setup_rhask() {
  if (!driver.init()) {
//    Serial.println("Driver init failed");
    while (true) {
      delay(1000);
    }
  }
}

uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
uint8_t buflen = 0;

void loop_rhask() {
  buflen = sizeof(uint8_t) * RH_ASK_MAX_MESSAGE_LEN;
  if (driver.recv(buf, &buflen)) {
//    Serial.print("Got: ");
//    Serial.print((char*)buf);
//    Serial.print(" (");
//    Serial.print(buflen);
//    Serial.println(")");
  }
  unsigned long now = millis();
  if (now - last_sent >= interval) {
    const char* msg = "bolzon";
    driver.send((uint8_t*) msg, strlen(msg));
    driver.waitPacketSent();
//    Serial.println("Sent");
    last_sent = now;
  }
}

void setup() {
  Serial.begin(115200);
//  Serial.print("Initializing... ");
#ifdef ESP8266
//  Serial.print("ESP8266... ");
#endif
  setup_rhask();
//  Serial.println("OK");
//  Serial.print("- TX PIN: ");
//  Serial.println(TX_PIN);
//  Serial.print("- RX PIN: ");
//  Serial.println(RX_PIN);

  pinMode(RX_PIN, INPUT);
}

void loop() {
  loop_rhask();
  Serial.println(digitalRead(RX_PIN));
  delay(100);
}*/

#define RX_PIN 10

void setup() {
  Serial.begin(115200);
  pinMode(RX_PIN, INPUT);
}

int count = 0;
byte last = 0;

void loop() {
  byte cur = digitalRead(RX_PIN);
  if (cur == last) {
    count++;
  }
  else {
    Serial.print("\n");
    last = cur;
    count = 0;
  }
  Serial.print(cur);
}
