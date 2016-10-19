## Garage Parking Assistant

This code controls an Arduino-based Garage Parking Assistant. The code and circuit were built based on the instructables by rclymer, which can be found at:
    http://www.instructables.com/id/Ultrasonic-Garage-Parking-Assistant-with-Arduino/

### Circuit
The circuit consists mainly of:
- ATtiny85 or Ardiuno board
- HC-SR04 Ultrasonic distance sensor
- Addressable RGB LED (a change from the original circuit)
- Push button

### Code
The code was built based on the original instructables, however it differs in many ways, namely:
- Code was significantly refactored to reflect better software engineering practices of encapsulation and separation of concerns
- Used a reliable library for detecting button push instead of manually detecting it
- Used Adafruit's NeoPixel library to control the addressable LED
- Added more zones and more colors:
-- Purple: Object too far
-- Green: Object within target distance
-- Yellow: Object Exited target distance (towards the sensor)
-- Red (blinking): Object too close. Back up.
