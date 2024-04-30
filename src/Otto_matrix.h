/*
 * MaxMatrix
 * Version 1.1 Feb 2023
 * Copyright 2013-2023 Oscar Kin-Chung Au
 * Adapted for OTTO version 9 use
 * 
 * This is a library for controlling MAX7219-based 8-digit LED matrices.
 * It provides functions for setting commands, intensity, columns, and dots,
 * as well as clearing the display and sending characters.
 */

#ifndef _Otto_matrix_H_
#define _Otto_matrix_H_

#include "Arduino.h"
#include "Otto_gestures.h"

#if defined(ESP32)
# include <SPI.h> // Include SPI library for ESP32
#endif

// Define the registers for the MAX7219
#define MAX7219_REG_NOOP        0x00 // No operation
#define MAX7219_REG_DIGIT0      0x01 // Digit 0
#define MAX7219_REG_DIGIT1      0x02 // Digit 1
#define MAX7219_REG_DIGIT2      0x03 // Digit 2
#define MAX7219_REG_DIGIT3      0x04 // Digit 3
#define MAX7219_REG_DIGIT4      0x05 // Digit 4
#define MAX7219_REG_DIGIT5      0x06 // Digit 5
#define MAX7219_REG_DIGIT6      0x07 // Digit 6
#define MAX7219_REG_DIGIT7      0x08 // Digit 7
#define MAX7219_REG_DECODE_MODE 0x09 // Decode mode
#define MAX7219_REG_INTENSITY   0x0a // Intensity
#define MAX7219_REG_SCAN_LIMIT  0x0b // Scan limit
#define MAX7219_REG_SHUTDOWN    0x0c // Shutdown
#define MAX7219_REG_DISPLAY_TEST 0x0f // Display test

class Otto_Matrix
{
  private:
    byte dataPin; // Data pin for the LED matrix
    byte loadPin; // Load pin for the LED matrix
    byte clockPin; // Clock pin for the LED matrix
    byte numDevices; // Number of devices in the matrix
    byte deviceBuffer[8]; // Buffer for device data
    byte charBuffer[80]; // Buffer for character data
    int rotationAngle; // Rotation angle for the matrix

    // Reload the matrix data
    void reload() { ... }

  public:
    Otto_Matrix(); // Default constructor

    // Initialize the matrix with the given pins, number of devices, and rotation angle
    void begin(byte data, byte load, byte clock, byte num, int rotation);

    // Clear the matrix display
    void clear();

    // Set a command and value for the matrix
    void setCommand(byte command, byte value);

    // Set the intensity of the matrix
    void setIntensity(byte intensity);

    // Set a column of the matrix to a value
    void setColumn(byte col, byte value);

    // Set all columns of a digit to a value
    void setColumnAll(byte col, byte value);

    // Set a dot in the matrix to a value
    void setDot(byte col, byte row, byte value);

    // Write a full 32-bit value to the matrix
    void writeFull(unsigned long value);

    // Send a character to the matrix at a given position, number, and scroll speed
    void sendChar(byte data, byte pos, byte number, byte scrollSpeed);
};

#endif
