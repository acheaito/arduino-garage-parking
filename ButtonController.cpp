#include <Arduino.h>
#include <Button.h>

#define DEBOUNCING_TIME_MS 15000

class ButtonController {
  private:
    Button button;
  public:
    ButtonController(int pin)
      : button (Button(pin)) {
      button.begin();
    }

    bool wasPressed() {
      return button.released();
    }
};

