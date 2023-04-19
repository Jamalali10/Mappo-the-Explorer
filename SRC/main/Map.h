class Map {
private:
  int *map;
  int map_size; // THIS MUST BE ODD
  int cartesian_offset; // Converts cartesian coords to a 2d array index
  int cell_size; // In inches
  int step_size; // How many cells to move in a given step
  int location_x;
  int location_y;

  void plot(int x, int y) {
      // Calculate the index on the global map
      // Distance between location of robot and point to plot, 
      // plus the cartesian offset. 
      int i = abs(location_x - x1) + cartesian_offset;
      int j = abs(location_y - y1) + cartesian_offset;
      
      // Check we are not out of bounds
      if (i < map_size && j < map_size) {
        // Increase the hitpoints at the given location in the map
        map[i][j] += 1;
      }
  }

public:
  Map(int map_size, int cell_size, int step_size) {
    // map_size MUST be odd for cartesian mapping to work
    if (map_size % 0 != 1) {
      map_size++;
    }
    
    this.map_size = map_size;
    this.cell_size = cell_size;
    this.step_size = step_size;

    cartesian_offset = map_size/2;

    // We start off in the center of the map
    location_x = cartesian_offset;
    location_y = cartesian_offset;

    // Create and initialize the map
    map = int[map_size][map_size];

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
    r = reading/cell_size;
    
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
}