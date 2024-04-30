//----------------------------------------------------------------
//-- Otto Dance smooth criminal
//-- This code will make Otto dance to the song "Smooth Criminal" by Michael Jackson
//-- https://www.ottodiy.com/
//-----------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>

#define N_SERVOS 4
#define INTERVALTIME 10.0

Servo servo[N_SERVOS];
Oscillator oscillator[N_SERVOS];

// Servo pins
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2

// Trim values for each servo
#define TRIM_RR 7
#define TRIM_RL 4
#define TRIM_YR -4
#define TRIM_YL -7

// EEPROM addresses for storing trim values
#define EEPROM_TRIM_ADDR_RR 0
#define EEPROM_TRIM_ADDR_RL 1
#define EEPROM_TRIM_ADDR_YR 2
#define EEPROM_TRIM_ADDR_YL 3

void setup() {
  Serial.begin(19200);

  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);

  // Read trim values from EEPROM
  bool eeprom_trim = EEPROM_TRIM;
  if (eeprom_trim) {
    for (int x = 0; x < N_SERVOS; x++) {
      int trim = EEPROM.read(EEPROM_TRIM_ADDR_RR + x);
      if (trim > 128) trim -= 256;
      servo[x].setTrim(trim);
      Serial.print("TRIM ");
      Serial.print(x);
      Serial.print(" en ");
      Serial.println(trim);
    }
  } else {
    // Set default trim values
    servo[0].setTrim(TRIM_RR);
    servo[1].setTrim(TRIM_RL);
    servo[2].setTrim(TRIM_YR);
    servo[3].setTrim(TRIM_YL);
  }

  // Initialize all servos to 90 degrees
  for (int i = 0; i < N_SERVOS; i++) {
    servo[i].write(90);
  }
}

void loop() {
  dance();
}

void dance() {
  primera_parte();
  segunda_parte();

  // Add the rest of the dance steps here
}

void primera_parte() {
  // Add the code for the first part of the dance here
}

void segunda_parte() {
  // Add the code for the second part of the dance here
}

// Helper function to move servos with specified angles and speeds
void move_servos(int servos[], int angles[], int speeds[], int duration) {
  for (int i = 0; i < N_SERVOS; i++) {
    servo[i].write(angles[i], speeds[i]);
  }
  delay(duration);
}

// Helper function to move servos with specified angles and equal speeds
void move_servos(int servos[], int angle, int speed, int duration) {
  for (int i = 0; i < N_SERVOS; i++) {
    servos[i].write(angle, speed);
  }
  delay(duration);
}

// Helper function to move servos with specified angles and equal speeds
void move_servos(int servos[], int angle, int duration) {
  for (int i = 0; i < N_SERVOS; i++) {
    servos[i].write(angle);
  }
  delay(duration);
}

// Helper function to move servos with specified angles and equal speeds
void move_servos(int servos[], int duration) {
  for (int i = 0; i < N_SERVOS; i++) {
    servos[i].write(servos[i].read() + duration);
  }
  delay(duration);
}

// Helper function to move servos with specified angles and equal speeds
void move_servos(int servos[], int angle_diff, int duration) {
  for (int i = 0; i < N_SERVOS; i++) {
    servos[i].write(servos[i].read() + angle_diff);
  }
  delay(duration);
}
