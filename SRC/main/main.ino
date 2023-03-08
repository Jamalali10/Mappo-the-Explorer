#include <Adafruit_MotorShield.h>
#include "RobotController.h"

AFMSController AFMS = AFMSController(70, Adafruit_MotorShield());
const int pingPin = 7;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  int val = analogRead(A0);
  
  // https://www.makerguides.com/sharp-gp2y0a21yk0f-ir-distance-sensor-arduino-tutorial/
  //int ir_cm = 29.988 * pow(val, -1.173);
  
  int ir_cm = exp(8.5841-log(val));
  long sonar_cm = distanceToObject();
  
  Serial.print("IR Value: ");
  Serial.println(ir_cm); 
  Serial.print("Sonar Value: ");
  Serial.println(sonar_cm);

  if(ir_cm < 15) {
    AFMS.backward();
  }

  if(sonar_cm < 15) {
    AFMS.forward();
  }

  delay(1000);
}

// This function also acts like delay(70)
long distanceToObject() {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  long duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  long cm = microsecondsToCentimeters(duration);

  return cm;
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
