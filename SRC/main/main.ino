#include <Adafruit_MotorShield.h>
#include "RobotController.h"

AFMSController AFMS = AFMSController(100, Adafruit_MotorShield());

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  int val = analogRead(A0);
  //int ir_cm = exp(8.5841-log(val));
  // https://www.makerguides.com/sharp-gp2y0a21yk0f-ir-distance-sensor-arduino-tutorial/
  //int ir_cm = 29.988 * pow(val, -1.173);
  int ir_cm = exp(8.5841-log(val));
  Serial.print("IR Value: ");
  Serial.println(ir_cm); 

  if(ir_cm < 15) {
    delay(500);
    AFMS.stop();
  }

  AFMS.stop();
  delay(10);
}
