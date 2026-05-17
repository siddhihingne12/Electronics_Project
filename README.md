# Electronics_Project

## Ultrasonic Gate Control

This repository contains an Arduino sketch for controlling a servo gate using an ultrasonic distance sensor.

### Files

- `GateController.ino`: Arduino sketch for detecting an object with an HC-SR04 ultrasonic sensor and moving a servo gate.

### Hardware Connections

- `trigPin` -> Arduino digital pin 9
- `echoPin` -> Arduino digital pin 8
- `servoPin` -> Arduino digital pin 7
- Ultrasonic Vcc -> 5V
- Ultrasonic GND -> GND
- Servo Vcc -> 5V (or external 5V supply if needed)
- Servo GND -> GND

### Components and Operation

- `SG90 Micro Servo Motor`: rotates between 0° and 180° based on Arduino commands.
  - At `0°`, the gate is closed.
  - At `90°` (or `180°`), the gate is open.
  - The servo converts electrical signals into mechanical movement to raise and lower the gate.
- `Battery`: provides DC power to the Arduino.
  - The Arduino then powers the ultrasonic sensor and servo motor.
- `Jumper Wires`: connect components on a breadboard or directly to the Arduino.

The system works like a mini IoT-based traffic gate, similar to real-world toll plazas. The Arduino monitors the sensor and moves the gate automatically when a car is detected.

### Overview

The sketch monitors distance using the ultrasonic sensor. When an object is detected within a threshold distance, it opens the servo gate. If the object is no longer present, the gate waits 2 seconds before closing.

### Code Explanation

1. `#include <Servo.h>`
   - Includes the Arduino Servo library to control the servo motor.

2. Pin definitions
   - `trigPin` is the ultrasonic trigger pin that sends the sound pulse.
   - `echoPin` is the ultrasonic echo pin that receives the reflected pulse.
   - `servoPin` is the pin used to control the servo motor.

3. Variables
   - `gateServo`: a Servo object used to set the servo angle.
   - `duration`: stores the ultrasonic pulse travel time.
   - `distance`: stores the calculated distance in centimeters.
   - `thresholdDistance`: the range in centimeters at which the gate detects a car.
   - `servoOpenAngle`: the servo position for an open gate.
   - `servoCloseAngle`: the servo position for a closed gate.
   - `gateOpenTime`: time when the gate was last opened or the car was last detected.
   - `delayBeforeClose`: how long the gate waits after the car disappears before closing (2 seconds).
   - `gateIsOpen`: current state of the gate.

4. `setup()`
   - Starts serial communication at 9600 baud for debugging and distance output.
   - Configures `trigPin` as `OUTPUT` and `echoPin` as `INPUT`.
   - Attaches the servo to `servoPin` and sets the gate to the closed position.

5. `loop()`
   - Sends a short ultrasonic pulse by toggling `trigPin` LOW for 2 microseconds, HIGH for 10 microseconds, then LOW again.
   - Uses `pulseIn(echoPin, HIGH)` to measure the time it takes for the echo to return.
   - Converts the measured `duration` into `distance` using the speed of sound formula: `distance = duration * 0.034 / 2`.
   - Prints the measured distance to the serial monitor for debugging.

6. Gate control logic
   - If a valid distance is detected and it is less than or equal to `thresholdDistance`:
     - If the gate is currently closed, the code opens the gate and updates `gateIsOpen`.
     - The code resets `gateOpenTime` while the object remains in range.
   - If the object leaves range:
     - The gate stays open until `delayBeforeClose` has passed since the last detection.
     - After the delay, the gate closes and `gateIsOpen` is set to false.

### Behavior Summary

- When a car enters the detection zone, the gate opens immediately.
- The gate remains open as long as the car is detected.
- When the car leaves, the gate closes after a 2 second delay.

### Usage

1. Upload `GateController.ino` to the Arduino.
2. Open the Serial Monitor at 9600 baud to view distance readings.
3. Place an object or vehicle within 15 cm of the ultrasonic sensor to trigger the gate.
