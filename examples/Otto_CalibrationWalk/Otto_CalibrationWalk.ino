#include <OttoDIY.h> // Include the Otto DIY library

// Create an instance of the Otto DIY class
OttoDIY myOtto;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Initialize the Otto DIY object
  myOtto.init(6, 7, 8, 9, 10, 11);

  // Calibrate the servos
  myOtto.calibrate();

  // Set the initial position of the Otto DIY robot
  myOtto.home();
}

void loop() {
  // Main loop for controlling the Otto DIY robot

  // Check for user input via the serial communication
  if (Serial.available() > 0) {
    // Read the user input
    int input = Serial.read();

    // Perform actions based on the user input
    switch (input) {
      case 'F':
        // Move forward
        myOtto.forward();
        break;
      case 'B':
        // Move backward
        myOtto.backward();
        break;
      case 'L':
        // Turn left
        myOtto.left();
        break;
      case 'R':
        // Turn right
        myOtto.right();
        break;
      case 'S':
        // Stop moving
        myOtto.stopMoving();
        break;
      default:
        // Ignore unrecognized input
        break;
    }
  }
}

