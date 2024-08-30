#include <Servo.h>

Servo myServo;  // Create a Servo object to control a servo

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 bps
  myServo.attach(9);   // Attach the servo on pin 9 to the Servo object
  Serial.println("Enter the desired degree (0 to 180):");
}

void loop() {
  if (Serial.available() > 0) {  // Check if data is available to read
    int degree = Serial.parseInt();  // Read the integer input from the serial monitor

    if (degree >= 0 && degree <= 180) {  // Ensure the degree is within the valid range
      myServo.write(degree);  // Move the servo to the specified degree
      Serial.print("Servo moved to: ");
      Serial.println(degree);
    } else {
      Serial.println("Invalid input. Please enter a value between 0 and 180.");
    }
  }
}
