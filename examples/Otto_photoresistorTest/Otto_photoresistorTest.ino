// Define the pin to which the photoresistor is connected
const int photoresistorPin = A0;

int sensorValue = 0;
float voltage_intensity = 0.0;
float lightPercentage = 0.0;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the photoresistor
  sensorValue = analogRead(photoresistorPin);

  if (sensorValue < 0 || sensorValue > 1023) {
    // Error: invalid sensor value
    Serial.println("Invalid sensor value");
    return;
  }

  voltage_intensity = (5.0 / 1023.0) * sensorValue;

  if (voltage_intensity < 0.0 || voltage_intensity > 5.0) {
    // Error: invalid voltage intensity
    Serial.println("Invalid voltage intensity");
    return;
  }

  lightPercentage = (voltage_intensity / 5.0) * 100.0;

  // Limit the light percentage to 100%
  if (lightPercentage > 100.0) {
    lightPercentage = 100.0;
  }

  // Print the sensor value to the Serial Monitor
  Serial.print("Light Percentage: ");
  Serial.print(lightPercentage);
  Serial.println("%");

  // Wait for a minimum delay of 100 milliseconds
  delay(100);
}
