#include "InternetButton.h"
#include "ntp-time.h"

InternetButton b = InternetButton();
NtpTime* ntpTime;
char buf[255];
static int i = 0;
static int alarm;

void setup() {
    ntpTime = new NtpTime(15);  // Do an ntp update every 15 minutes;
    ntpTime->start();
    alarm = Time.now() + 255 + 5;
    b.begin();
//    b.rainbow(10);
    b.allLedsOff();
}

#ifdef DEBUG
 #define DEBUG_PRINT(fmt, ...) sprintf(buf, fmt, __VA_ARGS__); Particle.publish("debug",buf); 
#else
 #define DEBUG_PRINT(fmt, ...)
#endif

int brightness(int when) {
  // 0 to 255 over the 30 minutes before the alarm time
  // pick a time for now as the target
  static int br = 0;
  int diff = when - Time.now();
  br = 0;
  if (diff < 0) {
    br = 255;
  } 
  if (diff < 255 && diff > 0) {
    br = 255 - diff;
  }
  
  DEBUG_PRINT("br %d %d %d", br, when, Time.now());
  return br;
}

void loop() {
    static unsigned long waitMillis = 0;
    int br;
    b.ledOn(0, 255,255,255);

    if(millis() > waitMillis) {
        DEBUG_PRINT("Clock is: %d", Time.now());
        waitMillis = millis() + (1000);
      br = brightness(alarm);
      b.allLedsOn(br, br, br);
    }

  delay(100);
}
