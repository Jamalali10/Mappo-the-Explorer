#pragma once
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class RobotController {
private:
  Adafruit_MotorShield AFMS;
  
  Adafruit_DCMotor *frontRightMotor;
  Adafruit_DCMotor *frontLeftMotor;
  Adafruit_DCMotor *backLeftMotor;
  Adafruit_DCMotor *backRightMotor;

  int defaultSpeed;
  float current_power_left_side;
  float current_power_right_side;

  // Converts a percent (0-1) to 0-255
  int percentToSpeed(float percent) {
    return percent*255;
  }

  void setSpeed(float percent) {
    int speed = percentToSpeed(percent);

    frontRightMotor->setSpeed(speed);
    frontLeftMotor->setSpeed(speed);
    backLeftMotor->setSpeed(speed);
    backRightMotor->setSpeed(speed);
  }

public:
   RobotController(float defaultSpeedPercent, Adafruit_MotorShield motorShield) {
    AFMS = motorShield;
    frontRightMotor = AFMS.getMotor(1);
    frontLeftMotor = AFMS.getMotor(2);
    backLeftMotor = AFMS.getMotor(3);
    backRightMotor = AFMS.getMotor(4);
    defaultSpeed = percentToSpeed(defaultSpeedPercent);
    current_power_left_side = defaultSpeed;
    current_power_right_side = defaultSpeed;
  }

  void begin() {
    AFMS.begin();
  }

  void forward(float speed){
    setSpeed(speed);

    frontRightMotor->run(FORWARD);
    frontLeftMotor->run(FORWARD);
    backLeftMotor->run(FORWARD);
    backRightMotor->run(FORWARD);
  }

  void forward() {
    forward(defaultSpeed);
  }

  void backward(float speed) {
    setSpeed(speed);

    frontRightMotor->run(BACKWARD);
    frontLeftMotor->run(BACKWARD);
    backLeftMotor->run(BACKWARD);
    backRightMotor->run(BACKWARD);
  }

  void backward() {
    backward(defaultSpeed);
  }

  void right(float speed) {
    setSpeed(speed);

    frontRightMotor->run(FORWARD);
    frontLeftMotor->run(BACKWARD);
    backLeftMotor->run(FORWARD);
    backRightMotor->run(BACKWARD);
  }

  void right() {
    right(defaultSpeed);
  }

  void rightSideForward(float percentSpeed) {
    int speed = percentToSpeed(percentSpeed);

    frontRightMotor->setSpeed(speed);
    backRightMotor->setSpeed(speed);
    frontRightMotor->run(FORWARD);
    backRightMotor->run(FORWARD);
  }

  void left(float speed) {
    setSpeed(speed);

    frontRightMotor->run(BACKWARD);
    frontLeftMotor->run(FORWARD);
    backLeftMotor->run(BACKWARD);
    backRightMotor->run(FORWARD);
  }

  void left() {
    left(defaultSpeed);
  }

  void leftSideForward(float percentSpeed) {
    int speed = percentToSpeed(percentSpeed);

    frontLeftMotor->setSpeed(speed);
    backLeftMotor->setSpeed(speed);
    frontLeftMotor->run(FORWARD);
    backLeftMotor->run(FORWARD);
  }

  void stop() {
    frontRightMotor->run(RELEASE);
    frontLeftMotor->run(RELEASE);
    backLeftMotor->run(RELEASE);
    backRightMotor->run(RELEASE);
  }

  float currentSpeedPercentLeft() {
    return current_power_left_side / 255;
  }

  float currentSpeedPercentRight() {
    return current_power_right_side / 255;
  }
};