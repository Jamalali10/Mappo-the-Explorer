#pragma once
#include "SlidingWindow.h"

class IR {
private:
  int pin;
  int windowSize;
  SlidingWindow readings;

public:
  IR() {
    IR(A0, 0);
  }

  IR(int readingPin, int sizeOfWindow) {
    pin = readingPin;
    windowSize = sizeOfWindow;
    readings = SlidingWindow(windowSize);
  }

  int readValue() {
    int val = analogRead(pin);

    // At some point we googled for this specific expression,
    // but idk where it is. Could probs find it again if needed.
    int ir_cm = exp(8.5841-log(val));
    
    if (windowSize != 0) {
      readings.push(ir_cm);
    }
    
    return ir_cm;
  }

  int noiseFilteredReading() {
    readValue();
    return readings.average();
  }

  String windowContents() {
    return readings.toString();
  }
};
