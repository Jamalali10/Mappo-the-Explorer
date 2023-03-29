#pragma once
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class RobotController {
private:
  Adafruit_MotorShield AFMS;
  
  Adafruit_DCMotor *forwardMotor1;
  Adafruit_DCMotor *forwardMotor2;
  Adafruit_DCMotor *backwardMotor1;
  Adafruit_DCMotor *backwardMotor2;

  int defaultSpeed;
  float current_power_left_side;
  float current_power_right_side;

  // Converts a percent (0-1) to 0-255
  int percentToSpeed(float percent) {
    return percent*255;
  }

  void setSpeed(float percent) {
    int speed = percentToSpeed(percent);

    forwardMotor1->setSpeed(speed);
    forwardMotor2->setSpeed(speed);
    backwardMotor1->setSpeed(speed);
    backwardMotor2->setSpeed(speed);
  }

public:
   RobotController(float defaultSpeedPercent, Adafruit_MotorShield motorShield) {
    AFMS = motorShield;
    forwardMotor1 = AFMS.getMotor(1);
    forwardMotor2 = AFMS.getMotor(2);
    backwardMotor1 = AFMS.getMotor(3);
    backwardMotor2 = AFMS.getMotor(4);
    defaultSpeed = percentToSpeed(speedDefault);
    current_power_left_side = defaultSpeed;
    current_power_right_side = defaultSpeed;
  }

  void begin() {
    AFMS.begin();
  }

  void forward(float speed){
    setSpeed(speed);

    forwardMotor1->run(FORWARD);
    forwardMotor2->run(FORWARD);
    backwardMotor1->run(FORWARD);
    backwardMotor2->run(FORWARD);
  }

  void forward() {
    forward(defaultSpeed);
  }

  void backward(float speed) {
    setSpeed(speed);

    forwardMotor1->run(BACKWARD);
    forwardMotor2->run(BACKWARD);
    backwardMotor1->run(BACKWARD);
    backwardMotor2->run(BACKWARD);
  }

  void backward() {
    backward(defaultSpeed);
  }

  void right(float speed) {
    setSpeed(speed);

    forwardMotor1->run(FORWARD);
    forwardMotor2->run(BACKWARD);
    backwardMotor1->run(FORWARD);
    backwardMotor2->run(BACKWARD);
  }

  void right() {
    right(defaultSpeed);
  }

  void rightSideForward(float percent) {
    int speed = percentToSpeed(percent);

    forwardMotor2->setSpeed(speed);
    backwardMotor2->setSpeed(speed);
    forwardMotor2->run(FORWARD);
    backwardMotor2->run(FORWARD);
  }

  void left(float speed) {
    setSpeed(speed);

    forwardMotor1->run(BACKWARD);
    forwardMotor2->run(FORWARD);
    backwardMotor1->run(BACKWARD);
    backwardMotor2->run(FORWARD);
  }

  void left() {
    left(defaultSpeed);
  }

  void leftSideForward(float percent) {
    int speed = percentToSpeed(percent);

    forwardMotor1->setSpeed(speed);
    backwardMotor1->setSpeed(speed);
    forwardMotor1->run(FORWARD);
    backwardMotor1->run(FORWARD);
  }

  void stop() {
    forwardMotor1->run(RELEASE);
    forwardMotor2->run(RELEASE);
    backwardMotor1->run(RELEASE);
    backwardMotor2->run(RELEASE);
  }

  float currentSpeedPercentLeft() {
    return current_power_left_side / 255;
  }

  float currentSpeedPercentRight() {
    return current_power_right_side / 255;
  }
};