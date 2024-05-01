class Oscillator {
  // Sinusoidal oscillation parameters
  // - frequency: The frequency of the oscillation in Hz
  // - amplitude: The amplitude of the oscillation in degrees
  // - phase: The phase shift of the oscillation in radians
  private:
    float frequency;  // The frequency of the oscillation in Hz
    float amplitude;  // The amplitude of the oscillation in degrees
    float phase;     // The phase shift of the oscillation in radians

  // Constructor for the Oscillator class
  // - params: 
  //   - freq: The initial frequency of the oscillation in Hz
  //   - amp: The initial amplitude of the oscillation in degrees
  //   - pha: The initial phase shift of the oscillation in radians
  public:
    Oscillator(float freq, float amp, float pha);

  // Accessor for the frequency of the oscillation
  // - returns: The frequency of the oscillation in Hz
  float getFrequency() const;

  // Accessor for the amplitude of the oscillation
  // - returns: The amplitude of the oscillation in degrees
  float getAmplitude() const;

  // Accessor for the phase shift of the oscillation
  // - returns: The phase shift of the oscillation in radians
  float getPhase() const;

  // Mutator for the frequency of the oscillation
  // - params:
  //   - freq: The new frequency of the oscillation in Hz
  void setFrequency(float freq);

  // Mutator for the amplitude of the oscillation
  // - params:
  //   - amp: The new amplitude of the oscillation in degrees
  void setAmplitude(float amp);

  // Mutator for the phase shift of the oscillation
  // - params:
  //   - pha: The new phase shift of the oscillation in radians
  void setPhase(float pha);

  // Method to calculate and return the next value of the oscillation
  // - returns: The next value of the oscillation
  float nextValue();
};
