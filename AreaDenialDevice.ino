#include <FastLED.h>
#include <HUSKYLENS.h>
#include <Wire.h>
#include <Servo.h>

// BB pins
#define LED_DATA_PIN 2
#define NUM_LEDS 1
#define LASER_PIN 5

#define BRIGHTNESS 15

// HUSKYLENS green line >> SDA-A4; blue line >> SCL-A5

CRGB leds[NUM_LEDS];
HUSKYLENS huskylens;
Servo XPanServo;
Servo YTiltServo;


const int defaultDegree = 90;
byte systemState = 0;

void setup() {

  // LED init

  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Serial monitor init

  Serial.begin(115200);
  Wire.begin();

  Serial.println("Serial Monitor Online");
  
  // Laser init
  
  pinMode(LASER_PIN, OUTPUT);
  digitalWrite(LASER_PIN, LOW);  // Ensure the laser is off at startup

  // Servo init

  XPanServo.attach(9);   // X servo = Pin 9
  YTiltServo.attach(10); // Y servo = Pin 10

  // Husky init

  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1. Please recheck the Protocol (I2C)"));
  Serial.println(F("2. Please recheck the connection."));
  delay(3000);
  }

}

void loop() {

  if (systemState = 0) {
    // Servo initialization function
    XPanServo.write(defaultDegree);
    YTiltServo.write(defaultDegree);

    Serial.println(F("State 0, Servos at middle"));
    systemState = 1;

  }


  if (systemState = 1) {

  Serial.println(F("State 1"));
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from Husky, check connection"));
    return;
  }

  if (!huskylens.isLearned()) {
    Serial.println(F("Nothing Learned"));
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    delay(1000);
  } 

  else if (!huskylens.available()) {
    Serial.println(F("No object detected"));
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    delay(1000);

  } 

  else {

    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      fill_solid(leds, NUM_LEDS, CRGB::Green);
      FastLED.show();
      
      }
    }
  }
}

void setLEDColor(CRGB color) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  }
}

void laserOn() {
  digitalWrite(LASER_PIN, HIGH);
}

void laserOff() {
  digitalWrite(LASER_PIN, LOW);
}
