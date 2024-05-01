#include <SerialCommand.h>

SerialCommand SCmd; // Create a SerialCommand object

void blinkLED() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  SCmd.addCommand("BLINK", blinkLED); // Add a command with a handler function
}

void loop() {
  SCmd.readSerial(); // Check for and process incoming serial commands
}


#include <SerialCommand.h>

SerialCommand SCmd; // Create a SerialCommand object

void setLED(char *argument) {
  int ledPin = atoi(argument);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void setup() {
  Serial.begin(9600);
  SCmd.addCommand("SETLED", setLED); // Add a command with a handler function
}

void loop() {
  SCmd.readSerial(); // Check for and process incoming serial commands
}
