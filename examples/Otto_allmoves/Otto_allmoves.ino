//----------------------------------------------------------------
//-- Otto All moves test
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------
#include <Otto.h>

// Define constants
#define LEFT_LEG 2
#define RIGHT_LEG 3
#define LEFT_FOOT 4
#define RIGHT_FOOT 5
#define BUZZER 13
#define DIN A3 // Data In pin
#define CS A2  // Chip Select pin
#define CLK A1 // Clock pin
#define ORIENTATION 1 // 8x8 LED Matrix orientation  Top  = 1, Bottom = 2, Left = 3, Right = 4 

// Initialize Otto object
Otto Otto(LEFT_LEG, RIGHT_LEG, LEFT_FOOT, RIGHT_FOOT, true, BUZZER);

void setup() {
  Otto.init(LEFT_LEG, RIGHT_LEG, LEFT_FOOT, RIGHT_FOOT, true, BUZZER); //Set the servo pins and Buzzer pin
  Otto.initMATRIX(DIN, CS, CLK, ORIENTATION);
  Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  Otto.playGesture(OttoHappy);
}

void loop() {
  performMoves();
  playSoundsAndGestures();
}

void performMoves() {
  Otto.walk(2, 1000, 1);
  Otto.walk(2, 1000, -1);
  Otto.turn(2, 1000, 1);
  Otto._tone(10, 3, 1);
  Otto.bendTones(100, 200, 1.04, 10, 10);
  Otto.home();
  Otto.turn(2, 1000, -1);
  Otto.bend(1, 500, 1);
  Otto.bend(1, 2000, -1);
  Otto.shakeLeg(1, 1500, 1);
  Otto.home();
  Otto.shakeLeg(1, 2000, -1);
  Otto.moonwalker(3, 1000, 25, 1);
  Otto.moonwalker(3, 1000, 25, -1);
  Otto.crusaito(2, 1000, 20, 1);
  Otto.crusaito(2, 1000, 20, -1);
  Otto.flapping(2, 1000, 20, 1);
  Otto.flapping(2, 1000, 20, -1);
  Otto.swing(2, 1000, 20);
  Otto.tiptoeSwing(2, 1000, 20);
  Otto.jitter(2, 1000, 20);
  Otto.updown(2, 1500, 20);
  Otto.ascendingTurn(2, 1000, 50);
  Otto.jump(1, 500);
  Otto.home();
}

void playSoundsAndGestures() {
  Otto.sing(S_cuddly);
  Otto.sing(S_OhOoh);
  Otto.sing(S_OhOoh2);
  Otto.sing(S_surprise);
  Otto.sing(S_buttonPushed);
  Otto.sing(S_mode1);
  Otto.sing(S_mode2);
  Otto.sing(S_mode3);
  Otto.sing(S_sleeping);
  Otto.sing(S_fart1);
  Otto.sing(S_fart2);
  Otto.sing(S_fart3);
  Otto.sing(S_happy);
  Otto.sing(S_happy_short);
  Otto.sing(S_superHappy);
  Otto.sing(S_sad);
  Otto.sing(S_confused);
  Otto.sing(S_disconnection);

  Otto.playGesture(OttoHappy);
  Otto.playGesture(OttoSuperHappy);
  Otto.playGesture(OttoSad);
  Otto.playGesture(OttoVictory);
  Otto.playGesture(OttoAngry);
  Otto.playGesture(OttoSleeping);
  Otto.playGesture(OttoFretful);
  Otto.playGesture(OttoLove);
  Otto.playGesture(OttoConfused);
  Otto.playGesture(OttoFart);
  Otto.playGesture(OttoWave);
  Otto.playGesture(OttoMagic);
  Otto.playGesture(OttoFail);

  Otto.putMouth(zero);
  Otto.putMouth(one);
  Otto.putMouth(two);
  Otto.putMouth(three);
  Otto.putMouth(four);
  Otto.putMouth(five);
  Otto.putMouth(6);
  Otto.putMouth(7);
  Otto.putMouth(8);
  Otto.putMouth(9);
  Otto.putMouth(smile);
  Otto.putMouth(happyOpen);
  Otto.putMouth(happyClosed);
  Otto.putMouth(heart);
  Otto.putMouth(angry);
  Otto.putMouth(smallSurprise);
  Otto.putMouth(bigSurprise);
  Otto.putMouth(tongueOut);
  Otto.putMouth(confused);
  Otto.putMouth(21);
  Otto.putMouth(27);
  Otto.putMouth(23);
  Otto.putMouth(24);
  Otto.putMouth(vamp1);
  Otto.putMouth(vamp2);
  Otto.putMouth(xMouth);
  Otto.putMouth(okMouth);
  Otto.putMouth(thunder);
  Otto.putMouth(lineMouth);
  Otto.putMouth(culito);

  Otto.putAnimationMouth(littleUuh, 0);
  Otto.putAnimationMouth(dreamMouth, 0);
  Otto.putAnimationMouth(dreamMouth, 1);
  Otto.putAnimationMouth(dreamMouth, 2);
}
