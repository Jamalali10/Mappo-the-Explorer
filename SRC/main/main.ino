//#include "RobotController.h"

#include <Adafruit_MotorShield.h>

class RobotController {
public:
  Adafruit_MotorShield AFMS;
  
  Adafruit_DCMotor *forwardMotor1;
  Adafruit_DCMotor *forwardMotor2;
  Adafruit_DCMotor *backwardMotor1;
  Adafruit_DCMotor *backwardMotor2;

  int defaultSpeed;

  void setSpeed(int speed) {
    forwardMotor1->setSpeed(speed);
    forwardMotor2->setSpeed(speed);
    backwardMotor1->setSpeed(speed);
    backwardMotor2->setSpeed(speed);
  }

   RobotController(int defaultSpeed) {
    AFMS = Adafruit_MotorShield(); 
    forwardMotor1 = AFMS.getMotor(1);
    forwardMotor2 = AFMS.getMotor(2);
    backwardMotor2 = AFMS.getMotor(3);
    backwardMotor2 = AFMS.getMotor(4);
  }

  void begin() {
    AFMS.begin();
  }

  void forward(int speed){
    setSpeed(speed);

    forwardMotor1->run(FORWARD);
    forwardMotor2->run(FORWARD);
    backwardMotor1->run(FORWARD);
    backwardMotor2->run(FORWARD);
  }

  void forward() {
    forward(defaultSpeed);
  }

  void backward(int speed) {
    setSpeed(speed);

    forwardMotor1->run(BACKWARD);
    forwardMotor2->run(BACKWARD);
    backwardMotor1->run(BACKWARD);
    backwardMotor2->run(BACKWARD);
  }

  void backward() {
    backward(defaultSpeed);
  }

  void right(int speed) {
    setSpeed(speed);

    forwardMotor1->run(FORWARD);
    forwardMotor2->run(BACKWARD);
    backwardMotor1->run(FORWARD);
    backwardMotor2->run(BACKWARD);
  }

  void right() {
    right(defaultSpeed);
  }

  void left(int speed) {
    setSpeed(speed);

    forwardMotor1->run(BACKWARD);
    forwardMotor2->run(FORWARD);
    backwardMotor1->run(BACKWARD);
    backwardMotor2->run(FORWARD);
  }

  void left() {
    left(defaultSpeed);
  }

  void stop() {
    forwardMotor1->run(RELEASE);
    forwardMotor2->run(RELEASE);
    backwardMotor1->run(RELEASE);
    backwardMotor2->run(RELEASE);
  }
};

RobotController robot = RobotController(128);

Adafruit_MotorShield AFMS;
  
  Adafruit_DCMotor *forwardMotor1;
  Adafruit_DCMotor *forwardMotor2;
  Adafruit_DCMotor *backwardMotor1;
  Adafruit_DCMotor *backwardMotor2;

void setup() {
  robot.begin();

  AFMS = Adafruit_MotorShield(); 
    forwardMotor1 = AFMS.getMotor(1);
    forwardMotor2 = AFMS.getMotor(2);
    backwardMotor2 = AFMS.getMotor(3);
    backwardMotor2 = AFMS.getMotor(4);
}

void loop() {
  int val = analogRead(A0);
  int ir_cm = exp(8.5841-log(val));

  forwardMotor1->run(FORWARD);
  /*
  robot.forward();
  delay(2000);
  robot.stop();
  delay(2000);
  robot.backward();
  delay(2000);*/
}
