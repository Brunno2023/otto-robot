/*
 * MaxMatrix
 * Version 1.1 Feb 2023
 * Copyright 2013-2023 Oscar Kin-Chung Au
 * Adapted for OTTO version 9 use
 */

#ifndef _Otto_matrix_H_
#define _Otto_matrix_H_

#include "Arduino.h"
#include "Otto_gestures.h"

#if defined(ESP32)
# include <SPI.h>
#endif

#define MAX7219_REG_NOOP        0x00
#define MAX7219_REG_DIGIT0      0x01
#define MAX7219_REG_DIGIT1      0x02
#define MAX7219_REG_DIGIT2      0x03
#define MAX7219_REG_DIGIT3      0x04
#define MAX7219_REG_DIGIT4      0x05
#define MAX7219_REG_DIGIT5      0x06
#define MAX7219_REG_DIGIT6      0x07
#define MAX7219_REG_DIGIT7      0x08
#define MAX7219_REG_DECODE_MODE 0x09
#define MAX7219_REG_INTENSITY   0x0a
#define MAX7219_REG_SCAN_LIMIT  0x0b
#define MAX7219_REG_SHUTDOWN    0x0c
#define MAX7219_REG_DISPLAY_TEST 0x0f

class Otto_Matrix
{
  private:
    byte dataPin;
    byte loadPin;
    byte clockPin;
    byte numDevices;
    byte deviceBuffer[8];
    byte charBuffer[80];
    int rotationAngle;

    void reload();

  public:
    Otto_Matrix();

    void begin(byte data, byte load, byte clock, byte num, int rotation);
    void clear();
    void setCommand(byte command, byte value);
    void setIntensity(byte intensity);
    void setColumn(byte col, byte value);
    void setColumnAll(byte col, byte value);
    void setDot(byte col, byte row, byte value);
    void writeFull(unsigned long value);
    void sendChar(byte data, byte pos, byte number, byte scrollSpeed);
};

#endif
