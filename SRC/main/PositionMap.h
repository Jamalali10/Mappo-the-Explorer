#pragma once
#include <math.h>

class PositionMap { 
private:
  const static int map_size = 85; // THIS MUST BE ODD
  char map[map_size][map_size];
  int cartesian_offset; // Converts cartesian coords to a 2d array index
  int cell_size; // In inches
  int step_size; // How many cells to move in a given step
  int location_x;
  int location_y;

  void plot(int x, int y) {
    int i = 0;
    int j = 0;

    // Determine quadrant with respect to the robot
    // Calculate the index on the global map
    // Calculation changes depending on what quadrant the point is in
    // with respect to the robot
    if (x >= 0 && y > 0) {
      // Quadrant 1
      i = location_x + x;
      j = location_y - y;
    }
    if (x < 0 && y <= 0) {
      // Quadrant 2
      i = location_x - x;
      j = location_y - y;
    }
    if (x <= 0 && y < 0) {
      // Quadrant 3
      i = location_x - x;
      j = location_y + y;
    }
    if (x > 0 && y <= 0) {
      // Quadrant 4
      i = location_x + x;
      j = location_y + y;
    }
    
    // Check we are not out of bounds
    if (i < map_size && j < map_size) {
      // Increase the hitpoints at the given location in the map
      map[i][j] += 1;
    }
  }

public:
  PositionMap(int cell_size, int step_size) {
    this->cell_size = cell_size;
    this->step_size = step_size;

    cartesian_offset = map_size/2;

    // We start off in the center of the map
    location_x = cartesian_offset;
    location_y = cartesian_offset;

    // Initialize the map
    for(int i = 0; i < map_size; i++) {
      for(int j = 0; j < map_size; j++) {
        map[i][j] = 0;
      }
    }
  }

  // Move +dx in x direction and +dy in y direction
  // Updates our location inside of the map
  void move(int dx, int dy) {
    location_x += dx;
    location_y += dy;
  }

  // r is the distance to the detected object
  // theta is TURN_ANGLE + SENSOR_ANGLE
  void plot_points(float theta, float r) {
    // Adjust for the cell size
    r = r/cell_size;
    
    // Convert from polar to cartesian coordinates
    float x1 = r * cos(theta);
    float y1 = r * sin(theta);

    // We want to go from where we detected the object to out beyond the map. 
    float x2 = map_size * cos(theta);
    float y2 = map_size * sin(theta);
    
    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);
    
    bool slope_less_than_one = false;

    if (dx > dy) {
      slope_less_than_one = true;
    }

    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;
 
    for (int i = 0; i <= dx; i++) {
      // checking either to decrement or increment the
      // value if we have to plot from (0,100) to (100,0)
      x1 < x2 ? x1++ : x1--;
      if (pk < 0) {
        // decision value will decide to plot
        // either x1 or y1 in x's position
        if (slope_less_than_one) {
                // putpixel(x1, y1, RED);
                plot(x1, y1);
                pk = pk + 2 * dy;
            }
            else {
                //(y1,x1) is passed in xt
                // putpixel(y1, x1, YELLOW);
                plot(y1, x1);
                pk = pk + 2 * dy;
            }
        }
        else {
            y1 < y2 ? y1++ : y1--;
            if (slope_less_than_one) {
                // putpixel(x1, y1, RED);
                plot(x1, y1);
            }
            else {
                //  putpixel(y1, x1, YELLOW);
                plot(y1, x1);
            }
            pk = pk + 2 * dy - 2 * dx;
        }
    }
  }

  int get(int i, int j) {
    return (int)map[i][j];
  }

  int size() {
    return map_size;
  }
};