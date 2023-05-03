#pragma once
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class RobotController {
private:
  static const float wheel_circumference = 7.42;

  Adafruit_MotorShield AFMS;
  
  Adafruit_DCMotor *frontRightMotor;
  Adafruit_DCMotor *frontLeftMotor;
  Adafruit_DCMotor *backLeftMotor;
  Adafruit_DCMotor *backRightMotor;

  float defaultSpeed;

  // Keeping track of current speed as percent
  float leftSideSpeed;
  float rightSideSpeed;

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
    defaultSpeed = defaultSpeedPercent;
    leftSideSpeed = defaultSpeed;
    rightSideSpeed = defaultSpeed;
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

  void right(float percentSpeed) {
    rightSideSpeed = percentSpeed;
    int speed = percentToSpeed(percentSpeed);

    frontRightMotor->setSpeed(speed);
    backRightMotor->setSpeed(speed);
    frontRightMotor->run(FORWARD);
    backRightMotor->run(FORWARD);
  }

  void right() {
    right(defaultSpeed);
  }

  void left(float percentSpeed) {
    leftSideSpeed = percentSpeed;
    int speed = percentToSpeed(percentSpeed);

    frontLeftMotor->setSpeed(speed);
    backLeftMotor->setSpeed(speed);
    frontLeftMotor->run(FORWARD);
    backLeftMotor->run(FORWARD);
  }

  void left() {
    left(defaultSpeed);
  }

  void stop() {
    leftSideSpeed = 0.0;
    rightSideSpeed = 0.0;

    frontRightMotor->run(RELEASE);
    frontLeftMotor->run(RELEASE);
    backLeftMotor->run(RELEASE);
    backRightMotor->run(RELEASE);
  }

  // Returns the current speed on the left side as a percentage
  float speedLeft() {
    return leftSideSpeed;
  }

  // Returns the current speed on the right side as a percentage
  float speedRight() {
    return rightSideSpeed;
  }

  // See the below link for differential drive calculation
  // https://robotics.stackexchange.com/questions/1653/calculate-position-of-differential-drive-robot
  // The above code has a case for when we're not going straight. However, because of how quickly we're calling
  // this function, we're basically always going straight I guess ¯\_(ツ)_/¯
  // TODO: Optimize by removing floating point arithmetic
  float mapNewLocation() {
    // leftDelta and rightDelta = distance that the left and right wheel have moved along the ground
    
    // Calculate revolutions per second - see Excel file in docs
    float leftRps = 0.166 * speedLeft();
    float rightRps = 0.166 * speedRight();

    // Time traveled since TIMESTAMP was last updated
    float timeTraveled = (millis() - TIMESTAMP) / 1000.0;

    float leftDelta = CIRCUMFERENCE * leftRps * timeTraveled;
    float rightDelta = CIRCUMFERENCE * rightRps * timeTraveled;

    new_x = 0
    new_y = 0
    new_heading = 0.0

    if (fabs(leftDelta - rightDelta) < 1.0e-6) {
      new_x = x + leftDelta * cos(heading);
      new_y = y + rightDelta * sin(heading);
      new_heading = heading;
    }
    else {
      float R = unitsAxisWidth * (leftDelta + rightDelta) / (2 * (rightDelta - leftDelta))
      float wd = (rightDelta - leftDelta) / unitsAxisWidth;

      new_x = x + R * sin(wd + heading) - R * sin(heading);
      new_y = y - R * cos(wd + heading) + R * cos(heading);
      new_heading = boundAngle(heading + wd);
    }
    
    map.move(x, y);
    robot.turn_angle(new_heading);
  }
};