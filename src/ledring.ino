#include "InternetButton.h"

InternetButton b = InternetButton();


// setup() runs once, when the device is first turned on.
void setup() {
    b.begin();
    b.rainbow(0);
}

int i = 0;

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  if (i<12) {
    b.ledOn(i, 255,255,255);
  }
  if (i>=12 && i<24) {
    b.advanceRainbow(256/12,0);
  }
  if (i==24) { i = 0; b.rainbow(0); }
  i++;
  delay(100);
}
