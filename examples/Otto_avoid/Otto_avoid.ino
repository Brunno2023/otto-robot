//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Otto avoid obstacles with ultrasonic sensor sample sketch code
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from <https://www.ottodiy.com/>
//-- Make sure to have installed all libraries: <https://github.com/OttoDIY/OttoDIYLib>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <Otto.h>
Otto Otto;  //This is Otto!

// Define the pins used by the ultrasonic sensor
#define TRIGGER_PIN 8
#define ECHO_PIN 9

// Define the maximum distance (in cm) that the sensor can detect
#define MAX_DISTANCE 200

// Define the minimum distance (in cm) that is considered an obstacle
#define MIN_DISTANCE 15

void setup() {
  Otto.init(2, 3, 4, 5, true, 13); //Set the servo pins and Buzzer pin

  // Initialize the ultrasonic sensor pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Measure the distance to the nearest obstacle
  long distance = getDistance();

  // If an obstacle is too close, avoid it
  if (distance <= MIN_DISTANCE) {
    Otto.sing(S_surprise);
    Otto.playGesture(OttoConfused);
    Otto.walk(2, 1000, -1); // BACKWARD x2
    Otto.turn(3, 1000, 1); // LEFT x3
  }
  // Otherwise, move forward
  else {
    Otto.walk(1, 1000, 1); // FORWARD x1
  }
}

// Measures the distance to the nearest obstacle using the ultrasonic sensor
long getDistance() {
  // Send a short pulse on the trigger pin
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the time it takes for the pulse to return
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Convert the time measurement to a distance in cm
  // The speed of sound is approximately 340 m/s, or 29 microseconds per cm
  return duration / 29 / 2;
}
