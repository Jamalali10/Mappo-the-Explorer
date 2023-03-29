#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include "IR.h"
#include <math.h>

int defaultRobotSpeed = 70;

RobotController robot = RobotController(defaultRobotSpeed, Adafruit_MotorShield());

// WindowSize for noise filtering. 0 if not utilizing
// I made this 0 because the window class is broke rn gotta debug
int windowSize = 0;
IR sensor[4] = {
  IR(A0, windowSize),
  IR(A1, windowSize),
  IR(A2, windowSize),
  IR(A3, windowSize)
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
  
//  for(int i = 0; i < 4; i++) {
//    ir_cm = sensor[i].readValue();
//    average += ir_cm;
//    Serial.print(ir_cm);
//    Serial.print(" ");
//  }
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
double convertSensorReadingToInches (rawSensorReading){
  double temp ;
}









