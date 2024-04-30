// Otto DIY App Firmware Version 13 with standard baudrate of 9600 for Bluetooth BLE modules.
// Otto DIY invests time and resources providing open source code and hardware,
// please support by purchasing kits from (https://www.ottodiy.com)
// Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib

#include <SerialCommand.h>
SoftwareSerial BTserial = SoftwareSerial(11, 12); // RX pin to 12 and TX pin to 11 on the board
SerialCommand SCmd(BTserial);
#include <Otto.h>
Otto Otto;

#define LeftLeg 2
#define RightLeg 3
#define LeftFoot 4
#define RightFoot 5
#define Buzzer 13
#define DIN A3 // Data In pin
#define CS A2  // Chip Select pin
#define CLK A1 // Clock pin
#define Orientation 1 // 8x8 LED Matrix orientation  Top  = 1, Bottom = 2, Left = 3, Right = 4
#define PIN_Button A0
#define PIN_ASSEMBLY 10

int T = 1000;
int moveId = 0;
int moveSize = 15;
volatile bool buttonPushed = false;
unsigned long int matrix;

void receiveStop() {
  sendAck();
  Otto.home();
  sendFinalAck();
}

void receiveLED() {
  sendAck();
  Otto.home();
  unsigned long int matrix;
  char *arg;
  char *endstr;
  arg = SCmd.next();
  if (arg != NULL) {
    matrix = strtoul(arg, &endstr, 2);
    Otto.putMouth(matrix, false);
  } else {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  }
  sendFinalAck();
}

void receiveBuzzer() {
  sendAck();
  Otto.home();
  bool error = false;
  int frec;
  int duration;
  char *arg;
  arg = SCmd.next();
  if (arg != NULL)
    frec = atoi(arg);
  else
    error = true;
  arg = SCmd.next();
  if (arg != NULL)
    duration = atoi(arg);
  else
    error = true;
  if (error == true) {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  } else {
    if (frec > 0 && duration > 0) {
      Otto._tone(frec, duration, 1);
    }
  }
  sendFinalAck();
}

void receiveTrims() {
  sendAck();
  Otto.home();
  int trim_YL, trim_YR, trim_RL, trim_RR;
  bool error = false;
  char *arg;
  arg = SCmd.next();
  if (arg != NULL)
    trim_YL = atoi(arg);
  else
    error = true;
  arg = SCmd.next();
  if (arg != NULL)
    trim_YR = atoi(arg);
  else
    error = true;
  arg = SCmd.next();
  if (arg != NULL)
    trim_RL = atoi(arg);
  else
    error = true;
  arg = SCmd.next();
  if (arg != NULL)
    trim_RR = atoi(arg);
  else
    error = true;
  if (error == true) {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  } else {
    if (trim_YL >= -90 && trim_YL <= 90 && trim_YR >= -90 && trim_YR <= 90 && trim_RL >= -90 && trim_RL <= 90 && trim_RR >= -90 && trim_RR <= 90) {
      Otto.setTrims(trim_YL, trim_YR, trim_RL, trim_RR);
      Otto.saveTrimsOnEEPROM();
    }
  }
  sendFinalAck();
}

void receiveServo() {
  sendAck();
  moveId = 30;
  bool error = false;
  int servo_YL, servo_YR, servo_RL, servo_RR;
  char *arg;
  arg = SCmd.next();
  if (arg != NULL)
    servo_YL = atoi(arg);
  else
    error = true;
  arg = SCmd.next();
  if (arg != NULL)
    servo_YR = atoi(arg);
  else
    error = true;
  arg = SCmd.next();
  if (arg != NULL)
    servo_RL = atoi(arg);
  else
    error = true;
  arg = SCmd.next();
  if (arg != NULL) {
    servo_RR = atoi(arg);
  } else
    error = true;
  if (error == true) {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
  } else {
    if (servo_YL >= 0 && servo_YL <= 180 && servo_YR >= 0 && servo_YR <= 180 && servo_RL >= 0 && servo_RL <= 180 && servo_RR >= 0 && servo_RR <= 180) {
      int servoPos[4] = {servo_YL, servo_YR, servo_RL, servo_RR};
      Otto._moveServos(200, servoPos);
    }
  }
  sendFinalAck();
}

void receiveMovement() {
  sendAck();
  if (Otto.getRestState() == true)
    Otto.setRestState(false);
  char *arg;
  arg = SCmd.next();
  if (arg != NULL)
    moveId = atoi(arg);
  else {
    Otto.putMouth(xMouth);
    delay(2000);
    Otto.clearMouth();
    moveId = 0;
  }
  arg = SCmd.next();
  if (arg != NULL)
    T = atoi(arg);
  else
    T = 1000;
  arg = SCmd.next();
  if (arg != NULL)
    moveSize = atoi(arg);
  else
    moveSize = 15;
}

void move(int moveId) {
  bool manualMode = false;
  if (moveId >= 0 && moveId < 21) {
    int speed = map(moveSize, 1, 100, 10, 255);
    int direction = (moveSize > 50) ? 1 : -1;
    switch (moveId) {
      case 0:
        Otto.home();
        break;
      case 1:
        Otto.walk(1, T, direction);
        break;
      case 2:
        Otto.turn(1, T, direction);
        break;
      case 3:
        Otto.updown(1, T, speed);
        break;
      case 4:
        Otto.moonwalker(1, T, speed, direction);
        break;
      case 5:
        Otto.swing(1, T, speed);
        break;
      case 6:
        Otto.crusaito(1, T, speed, direction);
        break;
      case 7:
        Otto.jump(1, T);
        break;
      case 8:
        Otto.flapping(1, T, speed, direction);
        break;
      case 9:
        Otto.tiptoeSwing(1, T, speed);
        break;
      case 10:
        Otto.bend(1, T, direction);
        break;
      case 11:
        Otto.shakeLeg(1, T, direction);
        break;
      case 12:
        Otto.jitter(1, T, speed);
        break;
      case 13:
        Otto.ascendingTurn(1, T, speed);
        break;
      default:
        manualMode = true;
        break;
    }
    if (!manualMode)
      sendFinalAck();
  }
}

void receiveGesture() {
  sendAck();
  Otto.home();
  int gesture = 0;
  char *arg;
  arg = SCmd.next();
  if (arg != NULL)
    gesture = atoi(arg);
  else
    delay(2000);
  if (gesture >= 1 && gesture <= 13) {
    Otto.playGesture((gesture_t)gesture);
  }
  sendFinalAck();
}

void receiveSing() {
  sendAck();
  Otto.home();
  int sing = 0;
  char *arg;
  arg = SCmd.next();
  if (arg != NULL)
    sing = atoi(arg);
  else
    delay(2000);
  if (sing >= 1 && sing <= 19) {
    Otto.sing((note_t)sing);
  }
  sendFinalAck();
}

void sendAck() {
  delay(30);
  Serial.print(F("&&"));
  Serial.print(F("A"));
  Serial.println(F("%%"));
  Serial.flush();
}

void sendFinalAck() {
  delay(30);
  Serial.print(F("&&"));
  Serial.print(F("F"));
  Serial.println(F("%%"));
  Serial.flush();
}

void ButtonPushed() {
  if (!buttonPushed) {
    buttonPushed = true;
    Otto.putMouth(smallSurprise);
  }
}

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  Otto.initMATRIX(DIN, CS, CLK, Orientation);
  Otto.matrixIntensity(7);
  pinMode(PIN_ASSEMBLY, INPUT_PULLUP);
  pinMode(PIN_Button, INPUT);

  SCmd.addCommand("S", receiveStop);
  SCmd.addCommand("L", receiveLED);
  SCmd.addCommand("T", receiveBuzzer);
  SCmd.addCommand("M", receiveMovement);
  SCmd.addCommand("H", receiveGesture);
  SCmd.addCommand("K", receiveSing);
  SCmd.addCommand("C", receiveTrims);
  SCmd.addCommand("G", receiveServo);
  SCmd.addDefaultHandler(receiveStop);

  Otto.sing(S_connection);
  Otto.home();
  for (int i = 0; i < 2; i++) {
    for (int i = 0; i < 8; i++) {
      Otto.putAnimationMouth(littleUuh, i);
      delay(150);
    }
  }
  Otto.putMouth(smile);
  Otto.sing(S_happy);
  delay(200);
  Otto.putMouth(happyOpen);

  while (digitalRead(PIN_ASSEMBLY) == LOW) {
    Otto.home();
    Otto.sing(S_happy_short); // sing every 5 seconds so we know OTTO is still working
    delay(5000);
  }
}

void loop() {
  SCmd.readSerial();
  if (Otto.getRestState() == false) {
    if (moveId >= 0 && moveId < 21) {
      move(moveId);
    }
  }
}
