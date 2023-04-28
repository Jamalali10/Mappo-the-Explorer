#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include "IR.h"
#include "PositionMap.h"
#include <math.h>

float defaultRobotSpeed = 0.70;

// Default velocity set, can change I guess

// Current angle of the robot in radians
float robot_turn_angle = 0.0;
RobotController robot = RobotController(defaultRobotSpeed, Adafruit_MotorShield());

int cell_size_inches = 6;
int step_size = 1; // How many cells to move per step
PositionMap pos_map = PositionMap(cell_size_inches, step_size);

// Sensors must be placed on the robot from left to right (when facing with the direction of travel.
// That is, you're behind the robot) for the ap_lite() algorithm to work.
// A6 is skipped because of the position of the motorboard over the arduino

// The sensor angle in radians. This angle is in respect to the velocity vector drawn when the robot is moving forward.
// Sensor offset degrees from left to right
// 45 degrees, 15 degrees, -15 degrees, -45 degrees
// Index here maps to the appropriate sensor index.

void setup() {
  Serial.begin(9600);
  robot.begin();
}

void loop() {
  //ap_lite();
  robot.stop();
  Serial.println(millis());
  pos_map.plot_points(PI/6, 0);
  
  
  for (int i = 0; i < pos_map.size(); i++) {
    for (int j = 0; j < pos_map.size(); j++) {
      Serial.print(pos_map.get(i, j));
      Serial.print(" ");
    }
    Serial.println();
  }

  delay(1000000);
}
  
void test_function() {
  robot.stop();
  robot.right();
  delay(5000);

  robot.stop();
  robot.left();
  delay(5000);
  robot.forward();
  robot.stop();
  delay(5000);

}