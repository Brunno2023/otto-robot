#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

#include "Arduino.h"

class Oscillator {
public:
    Oscillator();
    ~Oscillator();
    bool next_sample() noexcept;
    void attach(int pin, bool rev) noexcept;
    void detach() noexcept;
    void SetT(unsigned int T) noexcept;
    void SetPosition(int position) noexcept;
    void refresh() noexcept;
    void write(int position) noexcept;

private:
    Servo _servo;
    unsigned long _currentMillis;
    unsigned long _previousMillis;
    unsigned long _previousServoCommandMillis;
    unsigned int _samplingPeriod;
    unsigned int _period;
    unsigned int _numberSamples;
    float _inc;
    float _amplitude;
    float _phase;
    float _phase0;
    float _offset;
    bool _rev;
    bool _stop;
    int _pos;
    int _trim;
    int _diff_limit;
};

#endif /* OSCILLATOR_H_ */


#include "Oscillator.h"

Oscillator::Oscillator() noexcept
    : _servo(),
      _currentMillis(0),
      _previousMillis(0),
      _previousServoCommandMillis(0),
      _samplingPeriod(30),
      _period(2000),
      _numberSamples(0),
      _inc(0),
      _amplitude(45),
      _phase(0),
      _phase0(0),
      _offset(0),
      _rev(false),
      _stop(false),
      _pos(90),
      _trim(0),
      _diff_limit(0) {
    // empty
}

Oscillator::~Oscillator() noexcept = default;

bool Oscillator::next_sample() noexcept {
    _currentMillis = millis();
    if (_currentMillis - _previousMillis > _samplingPeriod) {
        _previousMillis = _currentMillis;
        return true;
    }
    return false;
}

void Oscillator::attach(int pin, bool rev) noexcept {
    if (!_servo.attached()) {
        _servo.attach(pin);
        _pos = 90;
        _servo.write(_pos);
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

void Oscillator::detach() noexcept {
    if (_servo.attached())
        _servo.detach();
}

void Oscillator::SetT(unsigned int T) noexcept {
    _period = T;

    _numberSamples = _period / _samplingPeriod;
    _inc = 2 * M_PI / _numberSamples;
}

void Oscillator::SetPosition(int position) noexcept {
    write(position);
}

void Oscillator::refresh() noexcept {
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

void Oscillator::write(int position) noexcept {
    long currentMillis = millis();
    if (_diff_limit > 0) {
        int limit = max(1, ((int)(currentMillis - _previousServoCommandMillis)) * _diff_limit / 1000);
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
