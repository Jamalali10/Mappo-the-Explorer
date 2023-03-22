#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include "IR.h"
 
int defaultRobotSpeed = 70;

RobotController robot = RobotController(defaultRobotSpeed, Adafruit_MotorShield());

// WindowSize for noise filtering. 0 if not utilizing
// I made this 0 because the window class is broke rn gotta debug
int windowSize = 0;
int irPins[4] = {A0, A1, A2, A3};
IR sensor[4];

void setup() {
  Serial.begin(9600);
  robot.begin();
  for(int i = 0; i < 4; i++) {
    sensor[i] = IR(irPins[i], windowSize);
  }
}

void loop() {
  robot.stop();

  for(int i = 0; i < 4; i++) {
    Serial.print("IR Values: ");
    Serial.print(sensor[i].readValue());
    Serial.print(" ");
  }

  Serial.println(" ");
  delay(200);

}
