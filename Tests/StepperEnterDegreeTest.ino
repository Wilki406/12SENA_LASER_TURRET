#include <Stepper.h>
#include <FastLED.h>

// Define the number of steps per revolution
const int stepsPerRevolution = 200;

// Initialize the stepper motor with the pins connected
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// Set the speed of the stepper motor in RPM (rotations per minute)
const int motorSpeed = 50;

// LED setup
#define LED_PIN     6
#define NUM_LEDS     1
CRGB leds[NUM_LEDS];

void setup() {
  // Set the speed of the motor in RPM
  myStepper.setSpeed(motorSpeed);

  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the LED strip
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.clear(); // Make sure the LED strip starts off
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    // Read the input value
    int degrees = Serial.parseInt();

    // Check if a valid degree value is received (non-zero)
    if (degrees != 0) {
      // Calculate the steps needed for the desired degrees
      long stepsToMove = (long) degrees * stepsPerRevolution / 360;

      // Turn the LED blue to indicate the motor is moving
      leds[0] = CRGB::Blue;
      FastLED.show();

      // Rotate the motor to the desired position
      myStepper.step(stepsToMove);

      // Print feedback to the serial monitor
      Serial.print("Moved ");
      Serial.print(degrees);
      Serial.println(" degrees.");

      // Turn off the LED after the motor has moved
      leds[0] = CRGB::Black;
      FastLED.show();
    } else {
      // Handle the case where degrees is zero or invalid
      Serial.println("No movement. Received invalid or zero degrees value.");
    }

    // Optionally, you can add a delay or other logic here
    delay(1000); // Delay for 1 second after each movement (optional)
  }
}
