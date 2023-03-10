#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include "Sonar.h"
#include "IR.h"

int sonarPin = 7;
int irPin = A0;
int defaultRobotSpeed = 70;

RobotController robot = RobotController(defaultRobotSpeed, Adafruit_MotorShield());
Sonar sonar = Sonar(sonarPin);
IR ir = IR(irPin);

void setup() {
  Serial.begin(9600);
  robot.begin();
}


int value = 100;
void loop() {
  int sonar_cm = sonar.noiseFilteredReading();
  int ir_cm = ir.noiseFilteredReading();
  
  Serial.print("IR Value: ");
  Serial.println(ir_cm); 
  Serial.print("Sonar Value: ");
  Serial.println(sonar_cm);
  Serial.println(sonar.windowContents());
  Serial.println(ir.windowContents());

  if(ir_cm < 13) {
    //robot.backward();
  }

  if(sonar_cm < 25) {
    //robot.forward();
  }
  robot.stop();
  delay(50);
}
