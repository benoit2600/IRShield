/*
    IRShield
    
    By Fauque Benoit
    Need the IRremote library (https://github.com/z3t0/Arduino-IRremote)
    The IR receiver must be connected on pin 6 and VCC 5V
    The IR led must be connected on pin 3 and VCC 5V
 */

#include <IRremote.h>

IRrecv irrecv(6);
IRsend irsend;
decode_results results;
boolean toggle = LOW;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    if(results.value == 1872){  // power on signal
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(11 * 1000);  // Wait until th TV start
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      for (int i = 0; i < 9; i++) {
        toggle = !toggle;
        digitalWrite(LED_BUILTIN, toggle);
        irsend.sendSony(2640, 12);  // Send the AV Signal. Need at least 3 signals send to be accepted by the TV.
        delay(40);
      }
      irrecv.enableIRIn(); // Start the receiver
      digitalWrite(LED_BUILTIN, LOW);
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
