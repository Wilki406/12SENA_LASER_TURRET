#include <Stepper.h>

// Define the number of steps per revolution
const int stepsPerRevolution = 200;

// Initialize the stepper motor with the pins connected
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// Set the speed of the stepper motor in RPM (rotations per minute)
const int motorSpeed = 50;

void setup() {
  // Set the speed of the motor in RPM
  myStepper.setSpeed(motorSpeed);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    // Read the input value
    int degrees = Serial.parseInt();

    // Calculate the steps needed for the desired degrees
    // 360 degrees corresponds to stepsPerRevolution steps   
    long stepsToMove = (long) degrees * stepsPerRevolution / 360;

    // Rotate the motor to the desired position
    myStepper.step(stepsToMove);

    // Print feedback to the serial monitor
    Serial.print("Moved ");
    Serial.print(degrees);
    Serial.println(" degrees.");
    
    // Optionally, you can add a delay or other logic here
    delay(1000); // Delay for 1 second after each movement (optional)
  }
}
