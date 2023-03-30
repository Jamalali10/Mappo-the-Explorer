#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include "IR.h"
#include <math.h>

int defaultRobotSpeed = 70;
float currentVelocity = 0.7;

RobotController robot = RobotController(defaultRobotSpeed, Adafruit_MotorShield());

// WindowSize for noise filtering. 0 if not utilizing
// I made this 0 because the window class is broke rn gotta debug
int windowSize = 0;

// Sensors must be placed on the robot from left to right (when facing with the direction of travel.
// That is, you're behind the robot) for the ap_lite() algorithm to work. Inner sensors face at 15 degrees,
// outer sensors look at 45 degrees.
IR sensor[4] = {
  IR(A0, windowSize),
  IR(A1, windowSize),
  IR(A2, windowSize),
  IR(A3, windowSize)
};

// The sensor angle in radians. This angle is in respect to the velocity vector drawn when the robot is moving forward.
// Index here maps to the appropriate sensor index.
float sensor_angle[4] = {
  0.7854,
  0.2618,
  0.2618,
  0.7854  
};

void setup() {
  Serial.begin(9600);
  robot.begin();
}

void loop() {
  robot.forward();
  int ir_cm = 0;

  Serial.print("IR Values: ");

  ir_cm = sensor[3].readValue();

  Serial.print(ir_cm);
  
  Serial.println(" ");

  delay(200);

  if (ir_cm < 15) {
    robot.backward();
    delay(1500);
  }
  else {
    robot.forward();
  }

  delay(100);

}

void ap_lite() {
  int reading_in; // the raw sensor reading AFTER being converted to inches
  int r; // sensor reading, with respect to range?
  float F; // Force 
  float delta_vx, delta_vy; // change in velocity in each direction
  float w; // Angle of the robot to turn

  // Power and speed are defined as a percentage of the maximum speed (0-1 inclusive)
  float power_left = 0.0;
  float power_right = 0.0;
  float MAX_SPEED = 0.7; // maximum power supply to motors
  int RANGE = 30; // reactive distance to an obstacle
  float STEP = 1.0; // step size of the robot
  float mass = 1.0; // mass of the robot (makes math easier)
  float kmid = 5.0; // Hooke's law constant for two middle sensors
  float kside = 4.0; //Hooke's law constant for two outside sensors (45 degree angle in our implementation)
  float FR = 0.5; // Friction
  float alpha = 1.0; // decides the amount to turn
  float Fx = 100.0; // attractive goal force in x direction
  float Fy = 0.0; // robot does not move side-ways hence it's 0
  float v = currentVelocity; // current velocity, initial value is 70%
  float vx = FR * v; // velocity drops with friction
  float vy = 0; // no side-ways velocity

  // for (all current sensors)
  for (int i = 0; i < 4; i++) {
    // Algorithm calls for the reading to be converted to inches.
    // Member function "readValue()" already does this.
    // "readValue()" also already filters for low readings.
    reading_in = sensor[i].readValue();
    theta = sensor_angle[i];

    r = RANGE - reading;
    if (r < 0) {
      // No obstacles seen
      r = 0;
    }

    // If we are reading from the middle sensors
    if (i == 1 || i == 2) {
      // compute force from the two middle sensors
      F = kmid * r; 
    }
    else {
      // compute force from the two out side sensors
      F = kside * r;
    }

    Fx = Fx - (F * cos(theta)); // Repulsive x component
    Fy = Fy - (F * sin(theta)); // Repulsive y component    
    }
  }

  delta_vx = STEP * Fx / mass; // change in velocity in x direction
  delta_vy = STEP * Fy / mass; // change in velocity in y direction

  vx += delta_vx; // add to velocity in x direction
  vy += delta_vy; // add to velocity in y direction

  v = sqrt(vx * vx + vy * vy); // current velocity

  delta = atan2(delta_vy, delta_vx); // direction of change in velocity
  w = turn_function(delta); // angle of the robot turn

  currentVelocity = v; // reset current velocity

  theta_new = atan2(vy, vx); // robot moves in first or second quadrant

  if ((-PI / 2.0 <= theta_new) && (theta_new <= PI/2.0)) {
    // Implicit cast to int. It's in the psuedocode
    power_right = (v + v * alpha * w) // power to right motor
    power_left = (v - v) * alpha * w) // power to left motor

    // proportionally cap the motor power
    if (power_right > MAX_SPEED || robot.currentSpeedPercentLeft() > MAX_SPEED) {
      if (power_right >= power_left) {
        power_left = MAX_SPEED * power_left / power_right;
        power_right = MAX_SPEED;
      }
      else {
        power_right = MAX_SPEED * power_right / power_left;
        power_left = MAX_SPEED;
      }
    }
  }


  // IF SOMETHING ISN"T WORKING REMEMBER THE PSUDOCODE SAID THAT POWER_LEFT AND RIGHT
  // WERE INTEGERS NOT FLOATS. There may be some conversion missing, even though
  // you convert the values inside the robot class.
  robot.leftSideForward(power_left);
  robot.rightSideForward(power_right);  
}

double turnFunction(double angle_rad){
// robot  moving to the second quadrant
  if ((PI / 2.0 < angle_rad) && (angle_rad <= PI)){
    angle_rad = PI - angle_rad;
  }
// robot moving to the third quadrant  
  else if ((-PI < angle_rad) && (angle_rad < -PI / 2.0)){
    angle_rad = -PI - angle_rad; //only used in backward move
  }
  return angle_rad;
}
float convertSensorReadingToInches(IR){
  float temp;
  temp = (6787.0/(IR- 3.0)) -4.0;
  return (temp/2.54);
}