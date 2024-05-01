#include <Otto.h>

// Create an instance of the Otto object
Otto myOtto;

void setup() {
  // Initialize the Otto object with the specified pins
  myOtto.init(2, 3, 4, 5, true, 6);
}

void loop() {
  // Move Otto to its home position
  myOtto.home();
  // Make Otto walk forward for 1000 milliseconds
  myOtto.walk(2, 1000, FORWARD);
  // Move Otto back to its home position
  myOtto.home();
  // Wait for 1000 milliseconds
  delay(1000);

  // Play the happy gesture
  myOtto.playGesture(OttoHappy);
  // Sing the happy song
  myOtto.sing(S_happy);

  // Define an array of oscillation amplitudes
  int A[4] = {30, 30, 20, 20};
  // Define an array of oscillation offsets
  int O[4] = {0, 0, 4, -4};
  // Define an array of phase differences
  double phase_diff[4] = {0, 0, DEG2RAD(-90), DEG2RAD(-90)};
  // Execute the oscillation with the specified parameters
  myOtto._execute(A, O, 1000, phase_diff);
}
