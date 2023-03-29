#pragma once
#include "SlidingWindow.h"

class IR {
private:
  int pin;
  int windowSize;
  SlidingWindow readings;

  // This value is arbitrarily set to be honest
  int minimumReading = 30;

public:
  IR() {
    IR(A0, 0);
  }

  IR(int readingPin) {
    pin = readingPin;
    windowSize = 0; // Hardcore disabling this for now
    readings = SlidingWindow(windowSize);
  }

  int readValue() {
    int val = 0;
    int ir_cm = 0;
    
    // Loop until we find a valid value
    bool validValue = false;
    while(validValue == false) {
      val = analogRead(pin);

      // If the voltage reading is less than or equal to the minimum 
      // it is probably a bad value. If it's greater than we continue 
      // with the program
      if (val > minimumReading) {
        validValue = true;
      }
    }
    
    // At some point we googled for this specific expression,
    // but idk where it is. Could probs find it again if needed.
    ir_cm = exp(8.5841-log(val));

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
