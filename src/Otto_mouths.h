// Header guard to prevent multiple inclusions of the header file
#ifndef OTTO_MOUTHS_H
#define OTTO_MOUTHS_H

// The number of mouth codes defined
const int NUM_MOUTHS = 31;

// Array of mouth codes as binary strings stored in program memory (PROGMEM)
const unsigned long int mouthCodes[NUM_MOUTHS] PROGMEM = { ... };

// Enumeration of mouth constants, each corresponding to a mouth code
enum MouthConstants {
  ZERO,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  SMILE,
  HAPPY_OPEN,
  HAPPY_CLOSED,
  HEART,
  BIG_SURPRISE,
  SMALL_SURPRISE,
  TONGUE_OUT,
  VAMP1,
  VAMP2,
  LINE_MOUTH,
  CONFUSED,
  DIAGONAL,
  SAD,
  SAD_OPEN,
  SAD_CLOSED,
  OK_MOUTH,
  X_MOUTH,
  INTERROGATION,
  THUNDER,
  CULITO,
  ANGRY
};

// Function to get the mouth code as a binary string
String getMouthCode(MouthConstants mouth) {
  return String((char*)pgm_read_word(&mouthCodes[mouth]), BIN);
}

// Function to print the mouth code to the serial monitor
void printMouthCode(MouthConstants mouth) {
  Serial.println(getMouthCode(mouth));
}

// Header guard closing
#endif // OTTO_MOUTHS_H
