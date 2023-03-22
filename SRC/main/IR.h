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
    int val = 0;
    int ir_cm = 0;
    

    bool validValue = false;
    while(validValue == false) {
      val = analogRead(pin);
      // At some point we googled for this specific expression,
      // but idk where it is. Could probs find it again if needed.
      ir_cm = exp(8.5841-log(val));

      // If it's less than or equal to 0 cm it is probably a bad value
      // If it's greater than we continue with the program
      if (ir_cm > 0) {
        validValue = true;
      }
    }
    
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
