#include <Arduino.h>
#include <NewPing.h>

#define MAX_DISTANCE_CM 500
#define DEFAULT_TARGET_DISTANCE_CM 30
#define PURPLE_ZONE_UPPER_BOUND_CM 100
#define INNER_TOLERANCE_CM 5
#define OUTER_TOLERANCE_CM 15
#define POWER_SAVE_MODE_THRESHOLD_MS 30000l
#define PING_ITERATIONS 10
#define ACCEPTABLE_CONSECUTIVE_READING_DIFF 50
#define MAX_ATTEMPTS 5

class SonarController {
  private:
    int triggerPin;
    int echoPin;
    int targetDistance;
    int distance;
    int lastDistance;
    NewPing sonar;
    unsigned long lastMovementMs;

    bool validReading(int distance, int lastDistance) {
      if (distance == 0) {
        return false;
      }
      if (lastDistance > 0 && abs(distance - lastDistance) > ACCEPTABLE_CONSECUTIVE_READING_DIFF) {
        return false;
      }
      return true;
    }

  public:
    SonarController(int triggerPin, int echoPin)
      : sonar (NewPing(triggerPin, echoPin, MAX_DISTANCE_CM))
      , targetDistance (DEFAULT_TARGET_DISTANCE_CM)
      , distance (0)
      , lastDistance (0)
      , lastMovementMs (0) {
    }

    int readDistance() {
      lastDistance = distance;
      int reading = MAX_DISTANCE_CM;
      int attempts = 0;
      do {
        reading = sonar.convert_cm(sonar.ping_median(PING_ITERATIONS));
        delay(100);
      } while (!validReading(reading, lastDistance) && attempts++ < MAX_ATTEMPTS);
      distance = reading;
      return reading;
    }

    void setTargetDistance(int newTargetDistance) {
      targetDistance = newTargetDistance;
    }

    boolean idleTimeoutReached() {
      if (!((distance >= lastDistance - INNER_TOLERANCE_CM) && (distance <= lastDistance + OUTER_TOLERANCE_CM))) {
        lastMovementMs = millis();
      }
      return (millis() - lastMovementMs) > POWER_SAVE_MODE_THRESHOLD_MS;
    }

    bool objectOutOfRange() {
      return distance >= MAX_DISTANCE_CM;
    }

    bool objectAwayFromTargetZone() {
      return (distance > targetDistance + OUTER_TOLERANCE_CM) && (distance < targetDistance + PURPLE_ZONE_UPPER_BOUND_CM);
    }

    bool objectInTargetZone() {
      return (distance >= targetDistance - INNER_TOLERANCE_CM) && (distance <= targetDistance + OUTER_TOLERANCE_CM);
    }

    bool objectPastTargetZone() {
      return (distance >= targetDistance - OUTER_TOLERANCE_CM) && (distance <= targetDistance - INNER_TOLERANCE_CM);
    }

    bool objectTooCloseToSensor() {
      return distance < targetDistance - OUTER_TOLERANCE_CM;
    }
};

