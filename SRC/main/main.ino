#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include "IR.h"
 
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
<<<<<<< HEAD
  delay(200);

=======

<<<<<<< HEAD
  if (ir_cm < 15) {
    robot.backward();
    delay(1500);
  }
  else {
    robot.forward();
  }

  delay(100);
>>>>>>> b5179545b721773fb9f4952673402f045d43337f
}
