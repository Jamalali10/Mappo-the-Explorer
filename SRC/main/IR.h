#pragma once
#include "SlidingWindow.h"

class IR {
private:
  int pin;
  int windowSize;
  SlidingWindow readings;

public:
  IR(int readingPin) {
    pin = readingPin;
    windowSize = 100;
    readings = SlidingWindow(windowSize);
  }

  int readValue() {
    int val = analogRead(pin);

    // At some point we googled for this specific expression,
    // but idk where it is. Could probs find it again if needed.
    int ir_cm = exp(8.5841-log(val));
    readings.push(ir_cm);

    return ir_cm;
  }

  int noiseFilteredReading() {
    readValue();
    return readings.average();
  }
};
