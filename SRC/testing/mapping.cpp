#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
int global_mapping [85][85]; //creating global mapping in 2D array
int Cell_size =6;
int STEP_size = 1;
//min range ditaction 
int min_range = 12;
//max range ditaction
int max_range = 30;
//creating local mapping in 2D array
int local[9][9];
int local_tablesize = 9; 
// position y
int y = 85/2;
// position x
int x = 85/2; 
//direction
int direction = 0;
//start in center of global map
int global_mapping [85][85] = {0};
// create a function for the mapping
void mapping(int sensor[4][4]);
// create a function for the mapping 4 sensor
void mapping_4_sensor(int sensor[4]);
//create a function for the local mapping
void local_mapping();
// create a function for the mapping
void mapping(int sensor[4][4]) {
    // create for loop for 4 the sensors
    for (int i = 0; i < 4; i++) {
        // create for loop for 4 the sensors
        for (int j = 0; j < 4; j++) {
            // create if statement for the sensors
            if (sensor[i][j] == 1) {
                // set the global map to 1
                global_mapping[x + i - 1][y + j - 1] = 1;
            }
        }
    }
}
// create a function for the mapping 4 sensor
void mapping_4_sensor(int sensor[4]) {
    // create for loop for 4 the sensors
    for (int i = 0; i < 4; i++) {
        // create if statement for the sensors
        if (sensor[i] < min_range) {
            // set the local map to 1
            local[0][i + 1] = 1;
        }
        // create else if statement for the sensors
        else if (sensor[i] > max_range) {
            // set the local map to 0
            local[0][i + 1] = 0;
        }
        // create else statement for the sensors
        else {
            // set the local map to 0
            local[0][i + 1] = 0;
        }
    }
}
// create a function for the local mapping
void local_mapping() {
    // create for loop for 4 the sensors
    for (int i = 0; i < 4; i++) {
        // create for loop for 4 the sensors
        for (int j = 0; j < 4; j++) {
            // create if statement for the sensors
            if (local[i][j] == 1) {
                // set the global map to 1
                global_mapping[x + i - 1][y + j - 1] = 1;
            }
        }
    }
}
// move to the next cell
void move() {
    // create if statement for the direction 
    if (direction == 0) {
        // move to the next cell
        y = y + STEP_size;
    }
    // create else if statement for the direction 
    else if (direction == 1) {
        // move to the next cell
        x = x + STEP_size;
    }
    // create else if statement for the direction 
    else if (direction == 2) {
        // move to the next cell
        y = y - STEP_size;
    }
    // create else if statement for the direction 
    else if (direction == 3) {
        // move to the next cell
        x = x - STEP_size;
    }
}
// turn using turn angle and sensor angle
void turn(int turn_angle, int sensor_angle) {
    // create if statement for the direction 
    if (turn_angle == 90) {
        // turn to the right
        direction = (direction + 1) % 4;
    }
    // create else if statement for the direction 
    else if (turn_angle == -90) {
        // turn to the left
        direction = (direction + 3) % 4;
    }
    // create else if statement for the direction 
    else if (turn_angle == 180) {
        // turn around
        direction = (direction + 2) % 4;
    }
    // create else if statement for the direction 
    else if (turn_angle == 0) {
        // do nothing
    }
    // create else statement for the direction 
    else {
        // do nothing
    }
}
// write the local to the global map
void write_local_to_global() {
    // create for loop for 4 the sensors
    for (int i = 0; i < local_tablesize; i++) {
        // create for loop for 4 the sensors
        for (int j = 0; j < local_tablesize; j++) {
          
                // set the global map 
                global_mapping[x - 4 + i][y + 4 + j] += local[i][j];
        }
    }
}

