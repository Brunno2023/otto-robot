// Define the pin to which the photoresistor is connected
const int photoresistorPin = A0;

int sensorValue = 0;
float voltage_intensity = 0.0;
float lightPercentage = 0.0;

void setup() {
  // Initialize Serial communication with a baud rate of 9600
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the photoresistor connected to pin A0
  sensorValue = analogRead(photoresistorPin);

  // Check if the sensor value is within the valid range (0-1023)
  if (sensorValue < 0 || sensorValue > 1023) {
    // Error: invalid sensor value
    Serial.println("Invalid sensor value");
    // Exit the function to prevent further execution with an invalid value
    return;
  }

  // Calculate the voltage intensity based on the sensor value
  voltage_intensity = (5.0 / 1023.0) * sensorValue;

  // Check if the voltage intensity is within the valid range (0.0-5.0V)
  if (voltage_intensity < 0.0 || voltage_intensity > 5.0) {
    // Error: invalid voltage intensity
    Serial.println("Invalid voltage intensity");
    // Exit the function to prevent further execution with an invalid value
    return;
  }

  // Calculate the light percentage based on the voltage intensity
  lightPercentage = (voltage_intensity / 5.0) * 100.0;

  // Limit the light percentage to 100%
  if (lightPercentage > 100.0) {
    lightPercentage = 100.0;
  }

  // Print the light percentage to the Serial Monitor
  Serial.print("Light Percentage: ");
  Serial.print(lightPercentage);
  Serial.println("%");

  // Wait for a minimum delay of 100 milliseconds before the next iteration
  delay(100);
}

