#include "RobotController.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
RobotController robot = RobotController(128, AFMS);

void setup() {
  robot.begin();
}

void loop() {
  int val = analogRead(A0);
  int ir_cm = exp(8.5841-log(val));

  robot.forward();
  delay(2000);
  robot.stop();
  delay(2000);
  robot.backward();
  delay(2000);
}
