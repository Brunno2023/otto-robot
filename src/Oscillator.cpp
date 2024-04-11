// Oscillator.cpp
// Generate sinusoidal oscillations in the servos
// (c) Juan Gonzalez-Gomez (Obijuan), Dec 2011
// GPL license
// https://github.com/Obijuan/ArduSnake/tree/master/ArduSnake
// http://www.iearobotics.com/wiki/index.php?title=ArduSnake:_Arduino_Modular_Snake_Robots_Library
// Used by OttoDIY Arduino Library project 2024


#include "Arduino.h"
#include "Oscillator.h"

// This function returns true if another sample should be taken (i.e. the TS time has passed since the last sample was taken)
bool Oscillator::next_sample() {
	// Read current time
	_currentMillis = millis();
  	// Check if the timeout has passed
	if(_currentMillis - _previousMillis > _samplingPeriod) {
		_previousMillis = _currentMillis;
 		return true;
	}
	return false;
}

//  Attach an oscillator to a servo
//  Input: pin is the arduino pin were the servo is connected
void Oscillator::attach(int pin, bool rev) {
	// If the oscillator is detached, attach it.
	if(!_servo.attached()) {
		// Attach the servo and move it to the home position
		_servo.attach(pin);
		_pos = 90;
		_servo.write(90);
		_previousServoCommandMillis = millis();
		// Initialization of oscilaltor parameters
		_samplingPeriod = 30;
		_period = 2000;
		_numberSamples = _period / _samplingPeriod;
		_inc = 2 * M_PI / _numberSamples;
		_previousMillis = 0;
		// Default parameters
		_amplitude = 45;
		_phase = 0;
		_phase0 = 0;
		_offset = 0;
		_stop = false;
		// Reverse mode
		_rev = rev;
	}
}

// Detach an oscillator from his servo
void Oscillator::detach() {
	// If the oscillator is attached, detach it.
	if(_servo.attached())
		_servo.detach();
}

// Set the oscillator period, in ms
void Oscillator::SetT(unsigned int T) {
	// Assign the new period
	_period = T;
	// Recalculate the parameters
	_numberSamples = _period / _samplingPeriod;
	_inc = 2 * M_PI / _numberSamples;
}

// Manual set of the position
void Oscillator::SetPosition(int position) {
	write(position);
}

// This function should be periodically called in order to maintain the oscillations. 
// It calculates if another sample should be taken and position the servo if so
void Oscillator::refresh() {
	// Only When TS milliseconds have passed, the new sample is obtained
	if(next_sample()) {
		// If the oscillator is not stopped, calculate the servo position
		if(!_stop) {
			// Sample the sine function and set the servo pos
			int pos = round(_amplitude * sin(_phase + _phase0) + _offset);
			if(_rev)
				pos = -pos;
			write(pos+90);
		}
		// Increment the phase
		// It is always increased, even when the oscillator is stop so that the coordination is always kept
		_phase = _phase + _inc;
	}
}

// Oscillator write position
void Oscillator::write(int position) {
	long currentMillis = millis();
	if(_diff_limit > 0) {
		int limit = max(1, (((int)(currentMillis - _previousServoCommandMillis)) * _diff_limit) / 1000);
		if(abs(position - _pos) > limit) {
			_pos += position < _pos ? -limit : limit;
 		} else {
			_pos = position;
		}
	} else {
		_pos = position;
	}
	_previousServoCommandMillis = currentMillis;
	_servo.write(_pos + _trim);
}
