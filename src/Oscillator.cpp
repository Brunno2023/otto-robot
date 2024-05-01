/**
 * @file Oscillator.h
 * @brief This file contains the definition of the Oscillator class, which
 * generates a sine wave and can be attached to a servo motor for physical
 * observation.
 */

#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

#include "Arduino.h"

/**
 * @class Oscillator
 * @brief This class implements an oscillator that generates a sine wave.
 * The oscillator can be attached to a servo motor to physically observe
 * the sine wave.
 */
class Oscillator {
public:
    /**
     * @brief Constructs an Oscillator object with default values.
     */
    Oscillator() noexcept;

    /**
     * @brief Destroys the Oscillator object.
     */
    ~Oscillator() noexcept = default;

    /**
     * @brief Advances the oscillator to the next sample.
     * @return True if a new sample is available, false otherwise.
     */
    bool next_sample() noexcept;

    /**
     * @brief Attaches the oscillator to a servo motor.
     * @param pin The pin number to attach the servo to.
     * @param rev If true, the sine wave will be inverted.
     */
    void attach(int pin, bool rev) noexcept;

    /**
     * @brief Detaches the oscillator from the servo motor.
     */
    void detach() noexcept;

    /**
     * @brief Sets the period of the sine wave in microseconds.
     * @param T The period of the sine wave.
     */
    void SetT(unsigned int T) noexcept;

    /**
     * @brief Sets the position of the servo motor.
     * @param position The position of the servo motor.
     */
    void SetPosition(int position) noexcept;

    /**
     * @brief Updates the oscillator's internal state.
     */
    void refresh() noexcept;

    /**
     * @brief Writes the position of the servo motor.
     * @param position The position of the servo motor.
     */
    void write(int position) noexcept;

private:
    Servo _servo; // The servo motor.
    unsigned long _currentMillis; // The current time in milliseconds.
    unsigned long _previousMillis; // The previous time in milliseconds.
    unsigned long _previousServoCommandMillis; // The previous time a servo command was sent.
    unsigned int _samplingPeriod; // The time between samples in milliseconds.
    unsigned int _period; // The period of the sine wave in microseconds.
    unsigned int _numberSamples; // The number of samples in one period.
    float _inc; // The increment in radians per sample.
    float _amplitude; // The amplitude of the sine wave.
    float _phase; // The phase of the sine wave.
    float _phase0; // The initial phase of the sine wave.
    float _offset; // The offset of the sine wave.
    bool _rev; // If true, the sine wave will be inverted.
    bool _stop; // If true, the oscillator will stop generating new samples.
    int _pos; // The current position of the servo motor.
    int _trim; // The trim value for the servo motor.
    int _diff_limit; // The maximum difference in position between samples.
};

#endif /* OSCILLATOR_H_ */

/**
 * @brief Constructs an Oscillator object with default values.
 */
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

/**
 * @brief Advances the oscillator to the next sample.
 * @return True if a new sample is available, false otherwise.
 */
bool Oscillator::next_sample() noexcept {
    _currentMillis = millis();
    if (_currentMillis - _previousMillis > _samplingPeriod) {
        _previousMillis = _currentMillis;
        return true;
    }
    return false;
}

/**
 * @brief Attaches the oscillator to a servo motor.
 * @param pin The pin number to attach the servo to.
 * @param rev If true, the sine wave will be inverted.
 */
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

/**
 * @brief Detaches the oscillator from the servo motor.
 */
void Oscillator::detach() noexcept {
    if (_servo.attached())
        _servo.detach();
}

/**
 * @brief Sets the period of the sine wave in microseconds.
 * @param T The period of the sine wave.
 */
void Oscillator::SetT(unsigned int T) noexcept {
    _period = T;

    _numberSamples = _period / _samplingPeriod;
    _inc = 2 * M_PI / _numberSamples;
}

/**
 * @brief Sets the position of the servo motor.
 * @param position The position of the servo motor.
 */
void Oscillator::SetPosition(int position) noexcept {
    write(position);
}

/**
 * @brief Updates the oscillator's internal state.
 */
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

/**
 * @brief Writes the position of the servo motor.
 * @param position The position of the servo motor.
 */
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
