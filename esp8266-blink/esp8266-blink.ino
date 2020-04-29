/* 
 * Blink example with serial prints.
 * Alexandre Bolzon <blzn@mail.ru>
 * April 2020
 */

// comment line below to disable serial prints

#define USE_SERIAL

// setup function
// runs at chip startup

void setup() {

#ifdef USE_SERIAL
  Serial.begin(115200);
  Serial.println("Initializing");
#endif

  pinMode(LED_BUILTIN, OUTPUT);
}

// loop function
// runs continuously while chip is on

void loop() {

  digitalWrite(LED_BUILTIN, LOW); // low = on

#ifdef USE_SERIAL
  Serial.println("Turned built-in LED on");
#endif

  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH); // high = off

#ifdef USE_SERIAL
  Serial.println("Turned built-in LED off");
#endif

  delay(1000);
}
