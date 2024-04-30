class Oscillator {
  private:
    // Sinusoidal oscillation parameters
    float frequency; // The frequency of the oscillation in Hz
    float amplitude; // The amplitude of the oscillation in degrees
    float phase; // The phase shift of the oscillation in radians

  public:
    // Constructor
    Oscillator(float freq, float amp, float pha);

    // Accessors
    float getFrequency() const;
    float getAmplitude() const;
    float getPhase() const;

    // Mutators
    void setFrequency(float freq);
    void setAmplitude(float amp);
    void setPhase(float pha);

    // Method to calculate the next oscillator value
    float nextValue();
};

