#include <Servo.h>

const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 7;

Servo gateServo;

long duration;
int distance;

const int thresholdDistance = 15; // cm to detect car
const int servoOpenAngle = 90;    // gate open angle
const int servoCloseAngle = 0;    // gate closed angle

unsigned long gateOpenTime = 0;
const unsigned long delayBeforeClose = 2000; // 2000 milliseconds = 2 seconds

bool gateIsOpen = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  gateServo.attach(servoPin);
  gateServo.write(servoCloseAngle); // gate starts closed
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance <= thresholdDistance) {
    if (!gateIsOpen) {
      Serial.println("Car detected - opening gate");
      gateServo.write(servoOpenAngle);
      gateIsOpen = true;
    }
    gateOpenTime = millis(); // Reset timer when car is present
  } else {
    // If car is not detected, check if delay time passed
    if (gateIsOpen && (millis() - gateOpenTime > delayBeforeClose)) {
      Serial.println("No car detected - closing gate");
      gateServo.write(servoCloseAngle);
      gateIsOpen = false;
    }
  }
}
