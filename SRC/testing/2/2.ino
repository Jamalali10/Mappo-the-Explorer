//#include <SharpIR.h>

#define IR A0 // define signal pin
#define model 20150 /
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *forward1Motor = AFMS.getMotor(1);
Adafruit_DCMotor *forward2Motor = AFMS.getMotor(2);
Adafruit_DCMotor *backward1Motor = AFMS.getMotor(3);
Adafruit_DCMotor *backward2Motor = AFMS.getMotor(4);
void setup() {
  AFMS.begin();
}

void loop (){
  forward (10);
  delay(3000);
  backward(10);
  delay(3000);

} 
void forward  (int speed){
  forward1Motor->setSpeed(speed);
  forward1Motor->run(FORWARD);
  forward2Motor->setSpeed(speed);
  forward2Motor->run(FORWARD);
  backward1Motor->setSpeed(speed);
  backward1Motor->run(FORWARD);
  backward2Motor->setSpeed(speed);
  backward2Motor->run(FORWARD);

}
void backward(int speed){
  forward1Motor->setSpeed(speed);
  forward1Motor->run(BACKWARD);
  forward2Motor->setSpeed(speed);
  forward2Motor->run(BACKWARD);
  backward1Motor->setSpeed(speed);
  backward1Motor->run(BACKWARD);
  backward2Motor->setSpeed(speed);
  backward2Motor->run(BACKWARD);

}


