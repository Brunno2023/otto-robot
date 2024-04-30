//-----------------------------------------------------------------
//-- This Otto uses a touch sensor to switch three modes
//-- Mode 1: Otto avoid obstacles
//-- Mode 2: Otto follow the hand
//-- Mode 3: Otto dances!
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------
#include <Otto.h>
Otto Otto;  //This is Otto!

//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*             -------- 
              |  O  O  |
              |--------|
  RIGHT LEG 3 |        | LEFT LEG 2
               -------- 
               ||     ||
RIGHT FOOT 5 |---     ---| LEFT FOOT 4  
*/
#define LeftLeg 2
#define RightLeg 3
#define LeftFoot 4
#define RightFoot 5
#define Buzzer 13
#define Trigger 8 // ultrasonic sensor trigger pin
#define Echo 9  // ultrasonic sensor echo pin
#define TouchSensor A0

const unsigned long kDebounceDelay = 50; // Debounce delay for touch sensor
unsigned long lastDebounceTime = 0;
int touchState = HIGH;
int lastTouchState = HIGH;

long ultrasound() {
  long duration, distance;
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration / 58;
  return distance;
}

int movement = 0;
boolean izqder = true; // TEMPO: 97 BPM
bool obstacleDetected = false;

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup() {
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  pinMode(TouchSensor, INPUT_PULLUP);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  Otto.home();
  Otto.sing(S_happy); // a happy Otto :)
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  int reading = digitalRead(TouchSensor);

  if (reading != lastTouchState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > kDebounceDelay) {
    if (reading != touchState) {
      touchState = reading;

      if (touchState == LOW) {
        movement++;
        Otto.sing(S_buttonPushed);
        delay(500);
      }
    }
  }

  lastTouchState = reading;

  switch (movement) {
    case 1:
      obstacleDetector();

      if (obstacleDetected) {
        Serial.println("OBJETO DETECTADO"); 
        Otto.sing(S_OhOoh);

        if (izqder) {
          Otto.walk(2, 1000, -1);
          Otto.turn(2, 1000, 1);
          izqder = false;
        } else {
          Otto.walk(2, 1000, -1);
          Otto.turn(2, 1000, -1);
          izqder = true;
        }

        obstacleDetector();
      } else {
        Otto.walk(1, 500, 1);
      }

      break;

    case 2:
      obstacleDetector();

      if (obstacleDetected) {
        Serial.println("Object detected");
        Otto.walk(2, 1000, 1);
        Otto.home();
        obstacleDetector();
      }

      break;

    case 3:
      danceRoutine();
      movement = 0;
      break;

    default:
      break;
  }
}

void obstacleDetector() {
  int distance = ultrasound();

  if (distance < 15) {
    obstacleDetected = true;
  } else {
    obstacleDetected = false;
  }
}

void danceRoutine() {
  Otto.jitter(10, 500, 40);
  Otto.home();
  Otto.moonwalker(2, 1000, 30, 1);
  Otto.home();
  Otto.ascendingTurn(2, 500, 50);
  Otto.home();
  Otto.tiptoeSwing(2, 1000, 30);
  Otto.home();
  Otto.flapping(2, 500, 40, 1);
  Otto.home();
  Otto.crusaito(2, 3000, 40, 1);
  Otto.home();
  Otto.shakeLeg(2, 1000, 1);
  Otto.home();
  Otto.sing(S_disconnection);
}
