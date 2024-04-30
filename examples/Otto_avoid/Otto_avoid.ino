//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This is the sample sketch code for Otto, an open-source DIY robot kit, to avoid obstacles using an ultrasonic sensor.
// The code is written for the Otto DIY library, which can be found at <https://github.com/OttoDIY/OttoDIYLib>.
// Please support Otto DIY by purchasing kits from <https://www.ottodiy.com/> if you find this code helpful.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <Otto.h> // Include the Otto library
Otto Otto;  //Create an instance of the Otto class

// Define the pins used by the ultrasonic sensor
#define TRIGGER_PIN 8
#define ECHO_PIN 9

// Define the maximum distance (in cm) that the sensor can detect
#define MAX_DISTANCE 200

// Define the minimum distance (in cm) that is considered an obstacle
#define MIN_DISTANCE 15

void setup() {
  Otto.init(2, 3, 4, 5, true, 13); //Initialize Otto by setting the servo pins and Buzzer pin

  // Initialize the ultrasonic sensor pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Measure the distance to the nearest obstacle
  long distance = getDistance();

  // If an obstacle is too close, avoid it
  if (distance <= MIN_DISTANCE) {
    Otto.sing(S_surprise); //Play a surprised sound
    Otto.playGesture(OttoConfused); //Play a confused gesture
    Otto.walk(2, 1000, -1); //Move backward twice
    Otto.turn(3, 1000, 1); //Turn left three times
  }
  // Otherwise, move forward
  else {
    Otto.walk(1, 1000, 1); //Move forward once
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

