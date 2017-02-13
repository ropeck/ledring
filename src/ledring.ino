#include "InternetButton.h"
#include "ntp-time.h"

InternetButton b = InternetButton();
NtpTime* ntpTime;
char buf[255];

void setup() {
    ntpTime = new NtpTime(15);  // Do an ntp update every 15 minutes;
    ntpTime->start();

    b.begin();
}

#ifdef DEBUG
 #define DEBUG_PRINT(fmt, ...) sprintf(buf, fmt, __VA_ARGS__); Particle.publish("debug",buf); 
#else
 #define DEBUG_PRINT(x)
#endif


void loop() {
    static unsigned long waitMillis = 0;
    static int i = 0;

    if(millis() > waitMillis) {
        DEBUG_PRINT("Clock is: %d", Time.now());
        waitMillis = millis() + (1000);
    }
  // starting 30 minutes before the alarm, set the LED brightness

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
