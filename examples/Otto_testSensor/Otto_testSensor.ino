//----------------------------------------------------------------
//-- Otto All moves test
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  pinMode( D5 , OUTPUT);    
  pinMode(2, OUTPUT);

  // Play the startup tone
  playTone(523, 125);
  playTone(587, 125);
  playTone(659, 125);
  playTone(698, 125);
  playTone(784, 125);
  playTone(880, 125);
  playTone(261, 125);

  // Wait for the serial connection to initialize
  delay(1000);
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////

void loop() {
  digitalWrite(2, LOW);

  Serial.println("LIGHT:");
  int lightValue = analogRead(A0);

  // Check that the light value is within a reasonable range
  if (lightValue >= 0 && lightValue <= 1023) {
    Serial.print(lightValue);
  }

  digitalWrite(2, HIGH);
  playTone(440, 125);

  // Add a delay so that the user can see and hear the output more clearly
  delay(250);
}

// Helper function to play a tone on pin D5
void playTone(int frequency, int duration) {
  tone(D5, frequency, duration);
  delay(duration);
}
