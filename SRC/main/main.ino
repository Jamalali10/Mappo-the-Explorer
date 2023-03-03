#include "RobotController.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
RobotController robot = RobotController(128, &AFMS);

  Adafruit_DCMotor *forwardMotor1;
  Adafruit_DCMotor *forwardMotor2;
  Adafruit_DCMotor *backwardMotor1;
  Adafruit_DCMotor *backwardMotor2;


void setup() {
  robot.begin();

  forwardMotor1 = AFMS.getMotor(1);
  forwardMotor2 = AFMS.getMotor(2);
  backwardMotor2 = AFMS.getMotor(3);
  backwardMotor2 = AFMS.getMotor(4);

  //robot.setMotors(forwardMotor1, forwardMotor2, backwardMotor1, backwardMotor2);
}

void loop() {
  int val = analogRead(A0);
  int ir_cm = exp(8.5841-log(val));

  robot.forward();
  delay(3000);
  robot.stop();

  //forwardMotor1->setSpeed(128);
  //forwardMotor1->run(FORWARD);
}
