#ifndef OTTO_MOUTHS_H
#define OTTO_MOUTHS_H

//***********************************************************************************
//*********************************MOUTHS DEFINES************************************
//***********************************************************************************

// The number of mouth codes defined
const int NUM_MOUTHS = 31;

// The mouth codes as binary strings
const unsigned long int mouthCodes[NUM_MOUTHS] PROGMEM = {
  0b00001100010010010010010010001100, //zero_code
  0b00000100001100000100000100001110, //one_code
  0b00001100010010000100001000011110, //two_code
  0b00001100010010000100010010001100, //three_code
  0b00010010010010011110000010000010, //four_code
  0b00011110010000011100000010011100, //five_code
  0b00000100001000011100010010001100, //six_code
  0b00011110000010000100001000010000, //seven_code
  0b00001100010010001100010010001100, //eight_code
  0b00001100010010001110000010001110, //nine_code
  0b00000000100001010010001100000000, //smile_code
  0b00000000111111010010001100000000, //happyOpen_code
  0b00000000111111011110000000000000, //happyClosed_code
  0b00010010101101100001010010001100, //heart_code
  0b00001100010010100001010010001100, //bigSurprise_code
  0b00000000000000001100001100000000, //smallSurprise_code
  0b00111111001001001001000110000000, //tongueOut_code
  0b00111111101101101101010010000000, //vamp1_code
  0b00111111101101010010000000000000, //vamp2_code
  0b00000000000000111111000000000000, //lineMouth_code
  0b00000000001000010101100010000000, //confused_code
  0b00100000010000001000000100000010, //diagonal_code
  0b00000000001100010010100001000000, //sad_code
  0b00000000001100010010111111000000, //sadOpen_code
  0b00000000001100011110110011000000, //sadClosed_code
  0b00000001000010010100001000000000, //okMouth_code
  0b00100001010010001100010010100001, //xMouth_code
  0b00001100010010000100000100000100, //interrogation_code
  0b00000100001000011100001000010000, //thunder_code
  0b00000000100001101101010010000000, //culito_code
  0b00000000011110100001100001000000  //angry_code
};

// Enumeration of mouth constants
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

#endif // OTTO_MOUTHS_H
