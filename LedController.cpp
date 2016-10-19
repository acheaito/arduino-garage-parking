#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class LedController {
  private:
    Adafruit_NeoPixel led;
    void setColor(int red, int green, int blue) {
      led.setPixelColor(0, led.Color(red , green , blue));
      led.show();
    }

  public:
    LedController(int dataPin)
      : led (Adafruit_NeoPixel(1, dataPin, NEO_RGB + NEO_KHZ800)) {
      led.begin();
    }

    void rgb(int red, int green, int blue) {
      setColor(red, green, blue);
    }

    void red() {
      setColor(255 , 0 , 0);
    }

    void green() {
      setColor(0 , 255 , 0);
    }

    void yellow() {
      setColor(200 , 50 , 0);
    }

    void purple() {
      setColor(255 , 0 , 255);
    }

    void flashRed(int delayMs) {
      off();
      delay(delayMs);
      red();
      delay(delayMs);
    }

    void flashGreen(int delayMs) {
      off();
      delay(delayMs);
      green();
      delay(delayMs);
    }

    void off() {
      led.setPixelColor(0, led.Color(0 , 0 , 0 ));
      led.show();
    }
};
