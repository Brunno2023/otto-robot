// Otto.h
// This is the header file for the Otto class, which is a software
// implementation of the Otto robot, a small, open-source,
// programmable robot designed for education and entertainment.
// The class provides functions for controlling the robot's motors,
// mouth, and LED matrix, as well as for playing sounds and gestures.

#ifndef OTTO_H
#define OTTO_H

#include <Arduino.h> // Include the Arduino library

#ifdef ARDUINO_ARCH_ESP32
#include <ESP32Servo.h> // Include the ESP32Servo library for ESP32 boards
#else
#include <Servo.h> // Include the Servo library for other boards
#endif

#include <Oscillator.h> // Include the Oscillator class
#include <EEPROM.h> // Include the EEPROM library for storing data in non-volatile memory
#include "Otto_sounds.h" // Include the Otto_sounds library
#include "Otto_gestures.h" // Include the Otto_gestures library
#include "Otto_mouths.h" // Include the Otto_mouths library
#include "Otto_matrix.h" // Include the Otto_matrix library

// Guard clause to prevent multiple inclusions of the same header file
#if defined(OTTO_H) && !defined(OTTO_IMPLEMENTATION)
#error "You cannot include 'Otto.h' directly, include 'Otto.cpp' instead."
#endif

// -- Constants
// Constants for defining the direction of motion
#define FORWARD 1
#define BACKWARD -1
#define LEFT 1
#define RIGHT -1

// Constants for defining the size of the motion
#define SMALL 5
#define MEDIUM 15
#define BIG 30

// -- Servo delta limit default. degree / sec
// Default limit for the servo delta, in degrees per second
#define SERVO_LIMIT_DEFAULT 240

class Otto
{
public:
    // Constructor
    // Initialize the Otto class with the servo pins, load calibration
    // data from EEPROM, and set the buzzer pin
    Otto(int YL, int YR, int RL, int RR, bool load_calibration, int Buzzer);

    // Otto initialization
    // Initialize the servos and set the initial position
    void init();

    // Attach & detach functions
    // Attach the servos to the pins
    void attachServos();

    // Detach the servos from the pins
    void detachServos();

    // Oscillator Trims
    // Set the trims for the servos
    void setTrims(int YL, int YR, int RL, int RR);

    // Save the trims to the EEPROM
    void saveTrimsOnEEPROM();

    // Predetermined Motion Functions
    // Move the servos to a specific position
    void _moveServos(int time, int servo_target[]);

    // Move a single servo to a specific position
    void _moveSingle(int position, int servo_number);

    // Oscillate the servos with specific parameters
    void oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle);

    // HOME = Otto at rest position
    // Move the Otto to the rest position
    void home();

    // Check if the Otto is at rest
    bool getRestState();

    // Set the rest state of the Otto
    void setRestState(bool state);

    // Predetermined Motion Functions
    // Jump with specific parameters
    void jump(float steps = 1, int T = 2000);

    // Walk with specific parameters
    void walk(float steps = 4, int T = 1000, int dir = FORWARD);

    // Turn with specific parameters
    void turn(float steps = 4, int T = 2000, int dir = LEFT);

    // Bend with specific parameters
    void bend(int steps = 1, int T = 1400, int dir = LEFT);

    // Shake leg with specific parameters
    void shakeLeg(int steps = 1, int T = 2000, int dir = RIGHT);

    // Updown with specific parameters
    void updown(float steps = 1, int T = 1000, int h = 20);

    // Swing with specific parameters
    void swing(float steps = 1, int T = 1000, int h = 20);

    // TiptoeSwing with specific parameters
    void tiptoeSwing(float steps = 1, int T = 900, int h = 20);

    // Jitter with specific parameters
    void jitter(float steps = 1, int T = 500, int h = 20);

    // AscendingTurn with specific parameters
    void ascendingTurn(float steps = 1, int T = 900, int h = 20);

    // Moonwalker with specific parameters
    void moonwalker(float steps = 1, int T = 900, int h = 20, int dir = LEFT);

    // Crusaito with specific parameters
    void crusaito(float steps = 1, int T = 900, int h = 20, int dir = FORWARD);

    // Flapping with specific parameters
    void flapping(float steps = 1, int T = 1000, int h = 20, int dir = FORWARD);

    // Mouth & Animations
    // Set the mouth shape with a predefined shape
    void putMouth(unsigned long int mouth, bool predefined = true);

    // Set the animation mouth shape with a specific animation and index
    void putAnimationMouth(unsigned long int anim, int index);

    // Clear the mouth shape
    void clearMouth();

    // Sounds
    // Play a tone with specific frequency and duration
    void _tone(float noteFrequency, long noteDuration, int silentDuration);

    // Bend tones with specific parameters
    void bendTones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);

    // Sing a song with a specific song name
    void sing(int songName);

    // Gestures
    // Play a gesture with a specific gesture index
    void playGesture(int gesture);

    // Initialize the LED matrix with specific pins and rotation
    void initMATRIX(int DIN, int CS, int CLK, int rotate);

    // Set the intensity of the LED matrix
    void matrixIntensity(int intensity);

    // Set the value of a specific LED on the matrix
    void setLed(byte X, byte Y, byte value);

    // Write text on the LED matrix with a specific scroll speed
    void writeText(const char *s, byte scrollspeed);

    // Servo limiter
    // Enable the servo limiter with a specific speed limit
    void enableServoLimit(int speed_limit_degree_per_sec = SERVO_LIMIT_DEFAULT);

    // Disable the servo limiter
    void disableServoLimit();

private:
    // Member variables
    Oscillator servo[4]; // Four oscillators for the servos
    Otto_Matrix ledmatrix; // LED matrix object
    int servo_pins[4]; // Array of servo pins
    int servo_trim[4]; // Array of servo trims

    int pinBuzzer; // Buzzer pin

    unsigned long final_time; // Final time for the motion
    unsigned long partial_time; // Partial time for the motion
    float increment[4]; // Increment for the motion

    bool isOttoResting; // Flag for the rest state of the Otto

    // Helper functions
    unsigned long int getMouthShape(int number); // Get the mouth shape with a specific number
    unsigned long int getAnimShape(int anim, int index); // Get the animation mouth shape with a specific animation and index
    void _execute(int A[4], int O[4], int T, double phase_diff[4], float steps); // Execute the motion with specific parameters

    // Error checking functions
    bool isValidServoPin(int pin); // Check if the servo pin is valid
    bool isValidBuzzerPin(int pin); // Check if the buzzer pin is valid
    bool isEEPROMAvailable(); // Check if the EEPROM is available
    bool areServosAttached(); // Check if the servos are attached
    bool areTrimsValid(int trims[4]); // Check if the trims are valid
    bool areLimitsValid(int limits[4]); // Check if the limits are valid
    bool isValidAnimationIndex(int index); // Check if the animation index is valid
    bool isValidGestureIndex(int index); // Check if the gesture index is valid
    bool areMatrixPinsValid(int DIN, int CS, int CLK); // Check if the matrix pins are valid
    bool isValidMatrixIntensity(int intensity); // Check if the matrix intensity is valid
    bool areMatrixLEDCoordinatesValid(byte X, byte Y); // Check if the matrix LED coordinates are valid
    bool isValidMatrixTextScrollSpeed(byte scrollspeed); // Check if the matrix text scroll speed is valid
};

#endif // OTTO_H
