#pragma once
#include "SlidingWindow.h"

class Sonar {
private:
  int pin;
  int windowSize;
  SlidingWindow readings;

  int microsecondsToInches(long microseconds) {
    // According to Parallax's datasheet for the PING))), there are 73.746
    // microseconds per inch (i.e. sound travels at 1130 feet per second).
    // This gives the distance travelled by the ping, outbound and return,
    // so we divide by 2 to get the distance of the obstacle.
    // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
    return microseconds / 74 / 2;
  }

  int microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the object we
    // take half of the distance travelled.
    return microseconds / 29 / 2;
  }

public:
  Sonar(int pingPin) {
    pin = pingPin;
    windowSize = 100;
    readings = SlidingWindow(windowSize);
  }

  int ping() {
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH pulse
    // whose duration is the time (in microseconds) from the sending of the ping
    // to the reception of its echo off of an object.
    pinMode(pin, INPUT);
    long duration = pulseIn(pin, HIGH);

    // convert the time into a distance and return
    int cm = microsecondsToCentimeters(duration);
    readings.push(cm);

    return cm;
  }

  int noiseFilteredReading() {
    ping();
    return readings.average();
  }

  String windowContents() {
    return readings.toString();
  }
};
