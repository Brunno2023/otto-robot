// OttoDIY Arduino Library project 2024

// (c) Juan Gonzalez-Gomez (Obijuan), Dec 2011 GPL license

#include "Arduino.h"
#include "Oscillator.h"

bool Oscillator::next_sample() {
    _currentMillis = millis();
    if (_currentMillis - _previousMillis > _samplingPeriod) {
        _previousMillis = _currentMillis;
        return true;
    }
    return false;
}

void Oscillator::attach(int pin, bool rev) {
    if (!_servo.attached()) {
        _servo.attach(pin);
        _pos = 90;
        _servo.write(90);
        _previousServoCommandMillis = millis();
        _samplingPeriod = 30;
        _period = 2000;
        _numberSamples = _period / _samplingPeriod;
        _inc = 2 * M_PI / _numberSamples;
        _previousMillis = 0;
        _amplitude = 45;
        _phase = 0;
        _phase0 = 0;
        _offset = 0;
        _stop = false;
        _rev = rev;
    }
}

void Oscillator::detach() {
    if (_servo.attached())
        _servo.detach();
}

void Oscillator::SetT(unsigned int T) {
    _period = T;
    _numberSamples = _period / _samplingPeriod;
    _inc = 2 * M_PI / _numberSamples;
}

void Oscillator::SetPosition(int position) {
    write(position);
}

void Oscillator::refresh() {
    if (next_sample()) {
        if (!_stop) {
            int pos = round(_amplitude * sin(_phase + _phase0) + _offset);
            if (_rev)
                pos = -pos;
            write(pos + 90);
        }
        _phase += _inc;
    }
}

void Oscillator::write(int position) {
    long currentMillis = millis();
    if (_diff_limit > 0) {
        int limit = max(1, (((int)(currentMillis - _previousServoCommandMillis)) * _diff_limit) / 1000);
        if (abs(position - _pos) > limit) {
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
