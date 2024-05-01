//----------------------------------------------------------------
//-- Otto All moves test
//--
//-- This is the main program for the Otto DIY robot, which tests
//-- all of its moves. Otto DIY invests time and resources in
//-- providing open-source code and hardware, so please support
//-- them by purchasing kits from https://www.ottodiy.com/.
//--
//-- Before running this code, make sure to install all the required
//-- libraries from this GitHub repository:
//-- https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////

void setup() {
  // Initialize the serial communication at a baud rate of 9600
  Serial.begin(9600);

  // Set the pin modes for D5 and 2 as outputs
  pinMode( D5 , OUTPUT);
  pinMode(2, OUTPUT);

  // Play the startup tone using the playTone function
  // The sequence of frequencies and durations corresponds to the
  // musical notes in the Otto DIY logo tune
  playTone(523, 125); // 523 Hz for 125 ms
  playTone(587, 125); // 587 Hz for 125 ms
  playTone(659, 125); // 659 Hz for 125 ms
  playTone(698, 125); // 698 Hz for 125 ms
  playTone(784, 125); // 784 Hz for 125 ms
  playTone(880, 125); // 880 Hz for 125 ms
  playTone(261, 125); // 261 Hz for 125 ms

  // Wait for the serial connection to initialize
  delay(1000);
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////

void loop() {
  // Set pin 2 to LOW (ground)
  digitalWrite(2, LOW);

  // Print a message to the serial monitor
  Serial.println("LIGHT:");

  // Read the analog value from pin A0 and store it in the lightValue variable
  int lightValue = analogRead(A0);

  // Check that the light value is within a reasonable range (0 to 1023)
  if (lightValue >= 0 && lightValue <= 1023) {
    // Print the lightValue to the serial monitor
    Serial.print(lightValue);
  }

  // Set pin 2 to HIGH (VCC)
  digitalWrite(2, HIGH);

  // Play a 440 Hz tone for 125 ms
  playTone(440, 125);

  // Add a delay so that the user can see and hear the output more clearly
  delay(250);
}

// Helper function to play a tone on pin D5
void playTone(int frequency, int duration) {
  // Play the tone using the built-in tone function
  tone(D5, frequency, duration);

  // Wait for the duration of the tone
  delay(duration);
}

