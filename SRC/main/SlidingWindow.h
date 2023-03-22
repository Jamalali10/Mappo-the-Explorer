
#pragma once

// Using a pointer for the array head cuz smart
//https://stackoverflow.com/questions/13431567/how-to-make-an-array-with-a-dynamic-size-general-usage-of-dynamic-arrays-maybe

class SlidingWindow {
private:
  int *window;
  int *windowCopy;
  int size;
  int arraySize;
 
public:
  SlidingWindow() {
    arraySize = 0;
    size = 0;
    window = new int[0];
    windowCopy = new int[0];
  }

  SlidingWindow(int windowSize) {
    arraySize = windowSize;
    size = 0;
    window = new int[windowSize];
    windowCopy = new int[windowSize];

    for (int i = 0; i < windowSize; i++) {
      window[i] = i;
      windowCopy[i] = i;
    }
  }

  ~SlidingWindow() {
    delete[] window;
  }

  void push(int reading) {
    if (size < arraySize) {
      window[size] = reading;
      size++;
    }
    // This is the case where we need to pop the end
    else {
      // We don't want the index to get down to 0 becuase we'll insert the reading there
      // Start at the end of the list and move each element over 1
      for (int i = size; 0 < i; i--) {
        window[i] = window[i-1];
      }
      // Put the new reading at the beginning
      window[0] = reading;
    }
  }

  // Technically this returns the median
  int average() {
    for(int i = 0; i < size; i++) {
      windowCopy[i] = window[i];
    }
    
    quickSort(windowCopy, size);

    return windowCopy[(size / 2)+1];
  }


  // Stolen from
  // https://forum.arduino.cc/t/some-sorting-algorithms-compared/271044/3
  void quickSort(int *ar, int n) 
  {
    if (n < 2)
    {
      // uint32_t s = freeRam();
      // if (fr > s) fr = s;
      return;
    }
    int p = ar[n / 2];
    int *l = ar;
    int *r = ar + n - 1;
    while (l <= r) {
      if (*l < p) {
        l++;
      }
      else if (*r > p) {
        r--;
      }
      else {
        int t = *l;
        *l = *r;
        *r = t;
        l++;
        r--;
      }
    }
    quickSort(ar, r - ar + 1);
    quickSort(l, ar + n - l);
  }

  String toString() {
    String str = "";

//    for (int i = 0; i < arraySize; i++) {
//      int item = window[i];
//      String concat = String(item);
//      str += concat + " ";
//    }
    str = String(window[0]);
    return str;
  }
};
