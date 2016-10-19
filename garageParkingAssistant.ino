#ifdef __AVR__
#include <avr/power.h>
#endif

#include "LedController.cpp"
#include "SonarController.cpp"
#include "ButtonController.cpp"

//I/O pins
#define TRIGGER_PIN 4
#define ECHO_PIN 3
#define LED_PIN 0
#define SETUP_BUTTON_PIN 1

#define DEFAULT_BAUD 9600

SonarController sonar = SonarController(TRIGGER_PIN, ECHO_PIN);
LedController led = LedController(LED_PIN);
ButtonController setupButton = ButtonController(SETUP_BUTTON_PIN);

void setup()
{
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 8000000) {
    clock_prescale_set(clock_div_1);
  }
#else
  Serial.begin(DEFAULT_BAUD);
#endif
  led.purple();
  logmsg("Started ", 0, "");
}

void loop() {
  int distance = sonar.readDistance();
  
  logmsg("Current distance", distance, "cm");

  if (sonar.idleTimeoutReached()) {
    led.off();
    logmsg("Power saving mode activate", 0, "");
  } else {
    setLedColor();
  }

  if (setupButton.wasPressed()) {
    sonar.setTargetDistance(distance);
    for (int i = 0; i < 3; i++) {
      led.flashGreen(50);
    }
    logmsg("+++++ Distance set to", distance, "cm");
  }
}

void setLedColor() {
  if (sonar.objectAwayFromTargetZone()) {
    led.purple();
  } else if (sonar.objectInTargetZone()) {
    led.green();
  } else if (sonar.objectPastTargetZone()) {
    led.yellow();
  } else if (sonar.objectTooCloseToSensor()) {
    led.flashRed(100);
  }
}

void logmsg(String preText, int reading, String postText) {
#if !defined (__AVR_ATtiny85__)
  String message = preText + " " + reading + " " + postText;
  Serial.println(message);
#endif
}
