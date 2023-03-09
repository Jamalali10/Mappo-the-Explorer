#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include "Sonar.h"
#include "IR.h"

int sonarPin = 7;
int irPin = A0;

RobotController robot = RobotController(70, Adafruit_MotorShield());
Sonar sonar = Sonar(sonarPin);
IR ir = IR(irPin);

void setup() {
  Serial.begin(9600);
  robot.begin();
}

void loop() {
  sonar.ping();
  ir.read();

  int sonar_cm = sonar.noiseFilteredReading();
  int ir_cm = ir.noiseFilteredReading();
  
  Serial.print("IR Value: ");
  Serial.println(ir_cm); 
  Serial.print("Sonar Value: ");
  Serial.println(sonar_cm);

  if(ir_cm < 15) {
    robot.backward();
  }

  if(sonar_cm < 15) {
    robot.forward();
  }

  delay(10);
}