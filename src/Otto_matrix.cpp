/*
 * MaxMatrix
 * Version 1.1 Feb 2023
 * Copyright 2013-2023 Oscar Kin-Chung Au
 * Adapted for OTTO version 9 use
 *
 * This code is for a MaxMatrix LED display controller using the Max7219 chip.
 * It includes initialization, intensity control, clearing the matrix, setting
 * commands, setting columns, and setting individual dots. Additionally, it has
 * functions for writing full values to the display, sending characters, and
 * scrolling text.
 */

#include "Arduino.h"
#include "Otto_matrix.h"

// Constructor for the Otto_Matrix class
Otto_Matrix::Otto_Matrix() 
{
	// Initialization of member variables
	//data = _data;
	//load = _load;
	//clock = _clock;
	//num = _num;
}

// Initialize the MaxMatrix with given parameters
void Otto_Matrix::init(byte _data, byte _load, byte _clock, byte _num, int _rotation)
{
  if (_data >= 64 || _load >= 64 || _clock >= 64 || _num > 8 || (_rotation != 1 && _rotation != 2 && _rotation != 3 && _rotation != 4)) {
    // Invalid parameters
    return;
  }

  data = _data;
  load = _load;
  clock = _clock;
  num = _num;
  rotation = _rotation;
  if (rotation < 1 || rotation > 4) rotation = 1; // we have to have number between 1 and 4
  for (int i=0; i<8; i++)
    buffer[i] = 0;

    for (int i=0; i<80; i++)
    CHARbuffer[i] = 0;
    
#if defined(ESP32)
    SPI.begin ( clock,  -1,  data, load);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setHwCs(true);
#else
    pinMode(data,  OUTPUT);
    pinMode(clock, OUTPUT);
    pinMode(load, OUTPUT);
    digitalWrite(clock, HIGH); 
#endif

        setCommand(max7219_reg_scanLimit, 0x07);      
	setCommand(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
	setCommand(max7219_reg_shutdown, 0x01);    // not in shutdown mode
	setCommand(max7219_reg_displayTest, 0x00); // no display test
	
	// empty registers, turn all LEDs off
	clearMatrix();
	
	setIntensity(0x0f);    // the first 0x0f is the value you can set
}

// Set the intensity of the display (0x00 to 0x0f)
void Otto_Matrix::setIntensity(byte intensity)
{
	setCommand(max7219_reg_intensity, intensity);
}

// Clear the matrix by turning all LEDs off
void Otto_Matrix::clearMatrix()
{
	for (int i=0; i<8; i++) 
		setColumnAll(i,0);
		
	for (int i=0; i<8; i++)
		buffer[i] = 0;

    for (int i=0; i<80; i++)
    CHARbuffer[i] = 0;
}

// Send a command to the Max7219 chip
void Otto_Matrix::setCommand(byte command, byte value)
{
#if defined(ESP32)
    SPI.transfer16((command << 8) | value);
#else
	digitalWrite(load, LOW);    
	for (int i=0; i<num; i++) 
	{
		shiftOut(data, clock, MSBFIRST, command);
		shiftOut(data, clock, MSBFIRST, value);
	}
	digitalWrite(load, LOW);
	digitalWrite(load, HIGH);
#endif
}

// Set a specific column of the matrix
void Otto_Matrix::setColumn(byte col, byte value)
{
	int n = col / 8;
	int c = col % 8;
#if defined(ESP32)
    for (int i=0; i<num; i++)
    {
	if (i == n)
        {
	    SPI.transfer16(((c + 1) << 8) | value);
	}
	//else
	//{
	//    SPI.transfer16(0);
	//}
    }
#else
	digitalWrite(load, LOW);    
        for (int i=0; i<num; i++) 
	{
		if (i == n)
		{
			shiftOut(data, clock, MSBFIRST, c + 1);
			shiftOut(data, clock, MSBFIRST, value);
		}
		//else
		//{
			//shiftOut(data, clock, MSBFIRST, 0);
			//shiftOut(data, clock, MSBFIRST, 0);
		//}
	}
	digitalWrite(load, LOW);
	digitalWrite(load, HIGH);
#endif
	
	buffer[col] = value;
}

// Set all dots in a column to a specific value
void Otto_Matrix::setColumnAll(byte col, byte value)
{
#if defined(ESP32)
    SPI.transfer16(((col + 1) << 8) | value);
#else
	digitalWrite(load, LOW);    
	for (int i=0; i<num; i++) 
	{
		shiftOut(data, clock, MSBFIRST, col + 1);
		shiftOut(data, clock, MSBFIRST, value);
	}
	digitalWrite(load, LOW);
	digitalWrite(load, HIGH);
#endif
	
	for (int i=0; i<num; i++)
		buffer[col * i] = value;
}

// Set a specific dot in the matrix
void Otto_Matrix::setDot(byte col, byte row, byte value)
{
    if (col >= 8 || row >= 8) {
      // Invalid parameters
      return;
    }
    bitWrite(buffer[col], row, value);

	int n = col / 8;
	int c = col % 8;
#if defined(ESP32)
    for (int i=0; i<num; i++) 
    {
	if (i == n)
	{
	    SPI.transfer16(((c + 1) << 8) | buffer[col]);
	}
	else
	{
	    SPI.transfer16(0);
	}
    }
#else
	digitalWrite(load, LOW);    
        for (int i=0; i<num; i++) 
	{
		if (i == n)
		{
			shiftOut(data, clock, MSBFIRST, c + 1);
			shiftOut(data, clock, MSBFIRST, buffer[col]);
		}
		else
		{
			shiftOut(data, clock, MSBFIRST, 0);
			shiftOut(data, clock, MSBFIRST, 0);
		}
	}
	digitalWrite(load, LOW);
	digitalWrite(load, HIGH);
#endif
}

// Write a full value to the display
void Otto_Matrix::writeFull(unsigned long value) {
  if (rotation < 1 || rotation > 4) rotation = 1;
  int startCol = 0;
  int startRow = 0;
  int endCol = 5;
  int endRow = 5;
  if (rotation == 2) {
    startCol = 1;
    endCol = 6;
  }
  else if (rotation == 3) {
    startCol = 0;
    endCol = 5;
    startRow = 1;
    endRow = 6;
  }
  else if (rotation == 4) {
    startCol = 1;
    endCol = 6;
    startRow = 1;
    endRow = 6;
  }
  for (int col = startCol; col <= endCol; col++) {
    for (int row = startRow; row <= endRow; row++) {
      if (col >= 6 || row >= 6) {
        // Invalid parameters
        return;
      }
      setDot(col, row, (1L & (value >> (row * 6 + col))));
    }
  }
}

// Send a character to the display
void Otto_Matrix::sendChar (const byte data, byte pos, byte number, byte scrollspeed)
{
  if (scrollspeed < 50 ) scrollspeed = 50;
   if (scrollspeed > 150 ) scrollspeed = 150;
  int charPos;
  if (rotation == 1) {
    charPos = pos * 8;
  }
  else if (rotation == 2) {
    charPos = (number - pos - 1) * 8;
  }
  else if (rotation == 3) {
    charPos = (number - pos - 1) * 8;
    charPos += 56;
  }
  else if (rotation == 4) {
    charPos = pos * 8;
    charPos += 56;
  }

  CHARbuffer[0 + charPos] = 0;
  CHARbuffer[1 + charPos] = pgm_read_byte(&Character_font_6x8[data].data[0]);
  CHARbuffer[2 + charPos] = pgm_read_byte(&Character_font_6x8[data].data[1]);
  CHARbuffer[3 + charPos] = pgm_read_byte(&Character_font_6x8[data].data[2]);
  CHARbuffer[4 + charPos] = pgm_read_byte(&Character_font_6x8[data].data[3]);
  CHARbuffer[5 + charPos] = pgm_read_byte(&Character_font_6x8[data].data[4]);
  CHARbuffer[6 + charPos] = pgm_read_byte(&Character_font_6x8[data].data[5]);
  CHARbuffer[7 + charPos] = 0;

 if (number == (pos + 1)){ // last character so display the total text
// we need to display first character and scroll left until each charater is shown.
    for (int c=0; c<8;c++){ // show first character
         byte value = CHARbuffer[c];
            for (int r=0; r<8; r++){
              if (rotation == 1) {
                setDot(c,7-r,(0b00000001 & (value >> r)));//       
                }
                if (rotation == 2) {
                 setDot(7-c,r,(0b00000001 & (value >> r)));//  
                }
                if (rotation == 3) {
                 //setDot(r,c,(1));// top LH corner
                 setDot(r,c,(0b00000001 & (value >> r)));//  
                }
                if (rotation == 4) {
                 setDot(7-r,7-c,(0b00000001 & (value >> r)));//  
                }
           }
      }
      delay(500); // show first digit for longer
      for (int i=0; i<((number*8)-1); i++){   // shift buffer the correct number of characters (8 lines per character)
        if (charPos + i + 1 < 80) {
          CHARbuffer[charPos + i] = CHARbuffer[charPos + i + 1];
        }
         for (int c=0; c<8;c++){ // 
             byte value = CHARbuffer[(1+c)+i];
                for (int r=0; r<8; r++){
                  if (rotation == 1) {
                  setDot(c,7-r,(0b00000001 & (value >> r)));//       
                   }
                  if (rotation == 2) {
                  setDot(7-c,r,(0b00000001 &
