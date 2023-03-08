#include <Adafruit_MotorShield.h>
#include "RobotController.h"
#include <queue>

AFMSController AFMS = AFMSController(70, Adafruit_MotorShield());
const int pingPin = 7;

int slidingWindowSize = 10;
queue<long> ir_values;
queue<long> sonar_values;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  int val = analogRead(A0);
  
  long ir_reading = exp(8.5841-log(val));
  long sonar_reading = distanceToObject();

  ir_values.push(ir_reading);
  sonar_values.push(sonar_reading);

  long ir_cm = averageValues(ir_values);
  long sonar_cm = averageValues(sonar_values);

  if (ir_values.size() > slidingWindowSize) {
    ir_values.pop();
  }
  if (sonar_values.size() > slidingWindowSize) {
    sonar_values.pop();
  }
  
  Serial.print("IR Value: ");
  Serial.println(ir_reading); 
  Serial.print("Sonar Value: ");
  Serial.println(sonar_reading);

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

long averageValues (queue<long> &values) {
  int count = 0;
  long sum = 0;
  
  for (auto it = values.cbegin(); it != values.cend(); it++) {
    sum += *it;
    count++;
  }

  return sum / count;
}
