#pragma once

// Using a pointer for the array head cuz smart
//https://stackoverflow.com/questions/13431567/how-to-make-an-array-with-a-dynamic-size-general-usage-of-dynamic-arrays-maybe

class SlidingWindow {
private:
  int *window;
  int currentSize;
  int arraySize;
 
public:
  SlidingWindow() {
    arraySize = 0;
    currentSize = 0;
    window = new int[0];
  }

  SlidingWindow(int windowSize) {
    arraySize = windowSize;
    currentSize = 0;
    window = new int[windowSize];

    for (int i = 0; i < windowSize; i++) {
      window[i] = i;
    }
  }

  ~SlidingWindow() {
    delete[] window;
  }

  void push(int reading) {
    if (currentSize < arraySize) {
      window[currentSize] = reading;
      currentSize++;
    }
    // This is the case where we need to pop the end
    else {
      // We don't want the index to get down to 0 becuase we'll insert the reading there
      // Start at the end of the list and move each element over 1
      for (int i = currentSize; 0 < i; i--) {
        window[i] = window[i-1];
      }
      // Put the new reading at the beginning
      window[0] = reading;
    }
  }

  int average() {
    int sum = 0;

    if (currentSize == 0) {
      return 0;
    }

    for (int i = 0; i < currentSize; i++) {
      sum += window[i];
    }

    return sum / currentSize;
  }
};
