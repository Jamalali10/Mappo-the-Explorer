#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"

class RobotController {
private:
  Adafruit_MotorShield *AFMS;
  
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

public:
   RobotController(int defaultSpeed, Adafruit_MotorShield *motorShield) {
    AFMS = motorShield;
    forwardMotor1 = AFMS->getMotor(1);
    forwardMotor2 = AFMS->getMotor(2);
    backwardMotor2 = AFMS->getMotor(3);
    backwardMotor2 = AFMS->getMotor(4);
  }

  void begin() {
    AFMS->begin();
  }

  void setMotors(Adafruit_DCMotor *m1, Adafruit_DCMotor *m2, Adafruit_DCMotor *m3, Adafruit_DCMotor* m4) {
    forwardMotor1 = m1;
    forwardMotor2 = m2;
    backwardMotor1 = m3;
    backwardMotor2 = m4;
  }

  void forward(int speed){
    forwardMotor1->setSpeed(speed);
    forwardMotor1->run(FORWARD);
    forwardMotor2->setSpeed(speed);
    forwardMotor2->run(FORWARD);
    backwardMotor1->setSpeed(speed);
    backwardMotor1->run(FORWARD);
    backwardMotor2->setSpeed(speed);
    backwardMotor2->run(FORWARD);
  }

  void forward() {
    forward(defaultSpeed);
  }

  void forward(Adafruit_DCMotor *m1) {
    forwardMotor1 = m1;

    setSpeed(128);
    forwardMotor1->run(FORWARD);
  }

  void backward(int speed) {
    forwardMotor1->setSpeed(speed);
    forwardMotor1->run(BACKWARD);
    forwardMotor2->setSpeed(speed);
    forwardMotor2->run(BACKWARD);
    backwardMotor1->setSpeed(speed);
    backwardMotor1->run(BACKWARD);
    backwardMotor2->setSpeed(speed);
    backwardMotor2->run(BACKWARD);
  }

  void backward() {
    backward(defaultSpeed);
  }

  void right(int speed) {
    forwardMotor1->setSpeed(speed);
    forwardMotor1->run(FORWARD);
    forwardMotor2->setSpeed(speed);
    forwardMotor2->run(BACKWARD);
    backwardMotor1->setSpeed(speed);
    backwardMotor1->run(FORWARD);
    backwardMotor2->setSpeed(speed);
    backwardMotor2->run(BACKWARD);
  }

  void right() {
    right(defaultSpeed);
  }

  void left(int speed) {
    forwardMotor1->setSpeed(speed);
    forwardMotor1->run(BACKWARD);
    forwardMotor2->setSpeed(speed);
    forwardMotor2->run(FORWARD);
    backwardMotor1->setSpeed(speed);
    backwardMotor1->run(BACKWARD);
    backwardMotor2->setSpeed(speed);
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
