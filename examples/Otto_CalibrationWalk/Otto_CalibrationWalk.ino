//----------------------------------------------------------------
// Copyright (c) 2021 Otto DIY
// This code is released under the MIT License. Please visit
// https://www.ottodiy.com/ for more information.
// Make sure to have installed all libraries:
// https://github.com/OttoDIY/OttoDIYLib
//----------------------------------------------------------------

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "Otto.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Define the Otto object
Otto Otto;

void setup() {
  // Set up the motor shield
  AFMS.begin();

  // Set up the Otto object with the motor shield and default pins
  Otto.init(AFMS);

  // Calibrate the servos
  Otto.calibrate();
}

void loop() {
  // Play the "Jingle Bells" melody
  Otto.play("JB");

  // Wait for the melody to finish
  delay(1000);

  // Play the "Ode to Joy" melody
  Otto.play("OJ");

  // Wait for the melody to finish
  delay(1000);
}
