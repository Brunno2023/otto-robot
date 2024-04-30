//----------------------------------------------------------------
//-- Otto Dance single ladies
//-- This code will make Otto dance to the song "Single Ladies" by Beyonce
//-- Otto DIY invests time and resources providing open source code and hardware,
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------

#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>

// Constants
#define N_SERVOS 4
#define EEPROM_TRIM_ADDRESS 0
#define EEPROM_TRIM_SIZE 4
#define TRIM_RR 18
#define TRIM_RL 18
#define TRIM_YR 26
#define TRIM_YL 18
#define PIN_RL 2
#define PIN_RR 3
#define PIN_YR 4
#define PIN_YL 5
#define INTERVALTIME 10.0

// Global variables
Oscillator servo[N_SERVOS];
int trim[N_SERVOS];

// Function prototypes
void dance();
void pasitos(int steps, int tempo);
void patada(int tempo);
void twist(int steps, int tempo);
void reverencia1(int steps, int tempo);
void reverencia2(int steps, int tempo);
void saludo(int steps, int tempo);
void upDown(int steps, int tempo);
void lateral_fuerte(boolean side, int tempo);
void run(int steps, int T);
void drunk(int tempo);
void kickLeft(int tempo);
void kickRight(int tempo);
void walk(int steps, int T);
void backyard(int steps, int T);
void moonWalkLeft(int steps, int T);
void moonWalkRight(int steps, int T);
void crusaito(int steps, int T);
void swing(int steps, int T);
void flapping(int steps, int T);

void setup() {
  Serial.begin(19200);

  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);

  // Load trim values from EEPROM
  for (int x = 0; x < N_SERVOS; x++) {
    trim[x] = EEPROM.read(EEPROM_TRIM_ADDRESS + x);
    if (trim[x] > 128) trim[x] -= 256;
    servo[x].SetTrim(trim[x]);
    Serial.print("TRIM ");
    Serial.print(x);
    Serial.print(" en ");
    Serial.println(trim[x]);
  }

  // Set initial position
  for (int i = 0; i < N_SERVOS; i++) servo[i].SetPosition(90);
}

void loop() {
  dance();
}

void dance() {
  pasitos(8, 620);
  crusaito(1, 620);
  patada(620);
  twist(2, 620);
  twist(3, 310);
  upDown(1, 1240);
  patada(1240);
  drunk(1240);
  flapping(1, 1240);
  walk(2, 620);
  walk(1, 1240);
  backyard(2, 3720);
  patada(1240);
  flapping(1, 1240);
  patada(1240);
  twist(8, 310);
  moonWalkLeft(2, 620);
  crusaito(1, 1240);

  lateral_fuerte(0, 620);
  lateral_fuerte(1, 620);
  upDown(1, 1240);

  saludo(1, 620);
  saludo(1, 310);
  delay(310);
  swing(3, 620);
  for (int i = 0; i < N_SERVOS; i++) servo[i].SetPosition(90);
  delay(310);

  lateral_fuerte(0, 620);
  lateral_fuerte(1, 620);
  lateral_fuerte(0, 310);
  lateral_fuerte(1, 310);
  lateral_fuerte(0, 310);
  delay(310);
  lateral_fuerte(0, 620);
  lateral_fuerte(1, 620);
  lateral_fuerte(0, 310);
  lateral_fuerte(1, 310);
  delay(310);

  pasitos(1, 620);
  pasitos(1, 310);
  delay(310);
  pasitos(1, 620);
  pasitos(1, 310);
  delay(310);

  crusaito(2, 620);
  crusaito(1, 1240);
  crusaito(2, 620);
  crusaito(1, 1240);
  crusaito(2, 620);
  crusaito(1, 1240);

  upDown(2, 620);
  crusaito(1, 1240);
  for (int i = 0; i < N_SERVOS; i++) servo[i].SetPosition(90);
  delay(310);
  pasitos(2, 1240);
  pasitos(2, 620);
  flapping(1, 1240);
  upDown(2, 620);
  upDown(1, 1240);

  for (int i = 0; i < 4; i++) {
    pasitos(1, 620);
    delay(310);
  }
  reverencia1(1, 2480);
  reverencia2(1, 2480);
  upDown(1, 620);
  run(2, 310);
  patada(1240);

  lateral_fuerte(0, 620);
  lateral_fuerte(1, 620);
  upDown(2, 620);
  lateral_fuerte(0, 620);
  lateral_fuerte(1, 620);
  upDown(2, 620);
  pasitos(4, 620);
  lateral_fuerte(0, 620);
  lateral_fuerte(1, 620);
  upDown(2, 620);

  patada(1240);
  pasitos(2, 620);
  patada(1240);
  pasitos(2, 620);
  swing(2, 1240);
  pasitos(4, 620);

  for (int i = 0; i < 4; i++) {
    lateral_fuerte(0, 620);
    lateral_fuerte(1, 620);
    lateral_fuerte(0, 310);
    lateral_fuerte(1, 310);
    lateral_fuerte(0, 310);
    delay(310);
  }

  pasitos(6, 620);
  delay(310);
  pasitos(1, 620);
  delay(310);
  pasitos(3, 620);
  delay(310);
  swing(4, 1240);

  twist(2, 310);
  delay(310);
  twist(2, 310);
  delay(310);

  drunk(1240);
  drunk(310);
  drunk(1240);
  delay(310);
  walk(1, 620);
  backyard(1, 620);

  servo[0].SetPosition(110);
  servo[1].SetPosition(130);
  delay(620);

  crusaito(3, 620);
  crusaito(1, 1240);
  upDown(1, 620);
  upDown(2, 310);

  kickLeft(310);
  kickRight(310);
  moonWalkLeft(1, 1240);
  moonWalkLeft(2, 620);
  moonWalkRight(1, 1240);
  moonWalkRight(2, 620);

  walk(4, 620);
  backyard(4, 620);

  lateral_fuerte(0, 620);
  lateral_fuerte(0, 620);
  lateral_fuerte(1, 620);
  lateral_fuerte(1, 620);
  walk(2, 620);
  backyard(2, 620);

  pasitos(6, 1240);
  swing(1, 620);
  upDown(1, 620);
  delay(620);
  upDown(6, 620);
  delay(620);

  for (int i = 0; i < 4; i++) {
    lateral_fuerte(0, 620);
    lateral_fuerte(1, 620);
  }

  delay(620);
  for (int i = 0; i < 7; i++) {
    pasitos(2, 620);
    swing(2, 620);
  }

  pasitos(1, 620);
  crusaito(1, 1240);
  upDown(1, 620);
}

void pasitos(int steps, int tempo) {
  int move1[4] = {90, 120, 60, 60};
  int move2[4] = {90, 90, 90, 90};
  int move3[4] = {60, 90, 120, 120};
  int move4[4] = {90, 90, 90, 90};

  for (int i = 0; i < steps; i++) {
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
    moveNServos(tempo * 0.25, move3);
    moveNServos(tempo * 0.25, move4);
  }
}

void patada(int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  servo[0].SetPosition(115);
  servo[1].SetPosition(120);
  delay(tempo / 4);
  servo[0].SetPosition(115);
  servo[1].SetPosition(70);
  delay(tempo / 4);
  servo[0].SetPosition(100);
  servo[1].SetPosition(80);
  delay(tempo / 4);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo / 4);
}

void twist(int steps, int tempo) {
  int move1[4] = {90, 90, 50, 130};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++) {
    moveNServos(tempo * 0.1, move1);
    moveNServos(tempo * 0.1, move2);
  }
}

void reverencia1(int steps, int tempo) {
  int move1[4] = {130, 50, 90, 90};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++) {
    moveNServos(tempo * 0.3, move1);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.3, move2);
  }
}

void reverencia2(int steps, int tempo) {
  int move1[4] = {130, 50, 90, 90};
  int move2[4] = {130, 50, 60, 120};
  int move3[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++) {
    moveNServos(tempo * 0.05, move1);
    moveNServos(tempo * 0.05, move2);
    moveNServos(tempo * 0.05, move1);
    moveNServos(tempo * 0.05, move2);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.1, move3);
  }
}

void saludo(int steps, int tempo) {
  int move1[4] = {60, 60, 90, 90};
  int move2[4] = {120, 60, 90, 90};

  for (int x = 0; x < steps; x++) {
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
  }
}

void upDown(int steps, int tempo) {
  int move1[4] = {50, 130, 90, 90};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++) {
    moveNServos(tempo * 0.2, move1);
    delay(tempo * 0.4);
    moveNServos(tempo * 0.2, move2);
  }
}

void lateral_fuerte(boolean side, int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  delay(tempo / 2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo / 2);
}

void run(int steps, int T) {
  int A[4] = {10, 10, 10, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {0, 0, DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++) oscillate(A, O, T, phase_diff);
}

void drunk(int tempo) {
  int move1[] = {60, 70, 90, 90};
  int move2[] = {110, 120, 90, 90};
  int move3[] = {60, 70, 90, 90};
  int move4[] = {110, 120, 90, 90};
  int move5[] = {90, 90, 90, 90};

  for (int i = 0; i < 5; i++) {
    moveNServos(tempo * 0.235, move1);
    moveNServos(tempo * 0.235, move2);
    moveNServos(tempo * 0.235, move3);
    moveNServos(tempo * 0.235, move4);
    moveNServos(tempo * 0.06, move5);
  }
}

void kickLeft(int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); // pie derecho
  servo[1].SetPosition(60); // pie izquierdo
  delay(tempo);
  servo[0].SetPosition(80); // pie derecho
  servo[1].SetPosition(60); // pie izquierdo
  delay(tempo / 4);
  servo[0].SetPosition(40); // pie derecho
  servo[1].SetPosition(60); // pie izquierdo
  delay(tempo / 4);
  servo[0].SetPosition(80); // pie derecho
  servo[1].SetPosition(60); // pie izquierdo
  delay(tempo / 4);
  servo[0].SetPosition(40); // pie derecho
  servo[1].SetPosition(60); // pie izquierdo
  delay(tempo / 4);
  servo[0].SetPosition(80); // pie derecho
  servo[1].SetPosition(60); // pie izquierdo
  delay(tempo);
}

void kickRight(int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(130); // pie izquierdo
  delay(tempo);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(100); // pie izquierdo
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(140); // pie izquierdo
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(80); // pie izquierdo
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(140); // pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); // pie derecho
  servo[1].SetPosition(100); // pie izquiero
  delay(tempo);
}

void walk(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {0, 0, DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++) oscillate(A, O, T, phase_diff);
}

void backyard(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {0, 0, DEG2RAD(-90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++) oscillate(A, O, T, phase_diff);
}

void moonWalkRight(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {0, DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++) oscillate(A, O, T, phase_diff);
}

void moonWalkLeft(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = {-15, 15, 0, 0};
  double phase_diff[4] = {0, DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i
