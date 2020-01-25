/* Dead air detector
    (c) A.G. Doswell 25 January 2020

    V1.0

    Arduino measures received audio on A0, and if there's been no audio for a while, flashes an LED connected to D7


*/

const long timeOut = 90000; // number of mS of dead air before LED is triggered.
unsigned long oldMillis;
const long flashInterval = 1000; //flash interval in mS
unsigned long deadTimer;
boolean led;

void setup() {

  pinMode (7, OUTPUT);

}

void loop() {
  unsigned long audioValue = analogRead (A0);
  if (audioValue >= 500 || audioValue <= 512) {
    deadTimer = deadTimer + (millis() - oldMillis);
  }
  else {
    deadTimer = 0;
  }
  if (deadTimer >= timeOut) {
    if (millis() - oldMillis > flashInterval) {
      if (led == LOW) {
        led = HIGH;
      }
      else {
        led = LOW;
      }
      digitalWrite (7, led);
    }
  }
  oldMillis = millis();
}
