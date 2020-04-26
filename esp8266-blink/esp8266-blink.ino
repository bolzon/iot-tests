/* 
 * Blink example with serial prints.
 * Alexandre Bolzon <blzn@mail.ru>
 * April 2020
 */

#define USE_SERIAL TRUE

void setup() {

#if USE_SERIAL
  Serial.begin(115200);
  Serial.println("Initializing");
#endif

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  digitalWrite(LED_BUILTIN, LOW); // low = on

#if USE_SERIAL
  Serial.println("Turned built-in LED on")
#endif

  delay(1500);
  digitalWrite(LED_BUILTIN, HIGH); // high = off

#if USE_SERIAL
  Serial.println("Turned built-in LED off")
#endif

  delay(3000);
}
