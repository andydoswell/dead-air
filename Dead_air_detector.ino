/* Dead air detector
    (c) A.G. Doswell 25 January 2020

    V1.0

    Arduino measures received audio from the VU drive precision rectifier on A0, and if there's been no audio for a while, flashes an LED connected to D7

*/

const long timeOut = 10000; // number of mS of dead air before LED is triggered.
unsigned long oldMillis;
const long flashInterval = 1000; //flash interval in mS
unsigned long flashTimer;
unsigned long deadTimer;
boolean led;
const unsigned int audioThreshold = 3; // Dead air detector threshold

void setup() {

  pinMode (13, OUTPUT);
}

void loop() {
  Serial.println();
  unsigned long audioValue = analogRead (A0);
  if (audioValue <= audioThreshold) {
    deadTimer = deadTimer + (millis() - oldMillis);
  }
  else {
    deadTimer = 0;
  }
  if (deadTimer >= timeOut) {
    if ((millis() - flashTimer) > flashInterval) {
      if (led == LOW) {
        led = HIGH;
        flashTimer = millis();
      }
      else {
        led = LOW;
        flashTimer = millis();
      }
    }
    digitalWrite (13, led);
  }
  else {
    led = false;
    digitalWrite (13, led);
  }
  oldMillis = millis();
}
