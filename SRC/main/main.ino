#include <Adafruit_MotorShield.h>
#include"RobotController.h"

AFMSController AFMS = AFMSController(255, Adafruit_MotorShield());

void setup() {
  AFMS.begin();
}

void loop() {
  int val = analogRead(A0);
  int ir_cm = exp(8.5841-log(val));

  AFMS.forward();
  delay(2000);
  AFMS.stop();
  delay(2000);
  AFMS.backward();
  delay(2000);
}
