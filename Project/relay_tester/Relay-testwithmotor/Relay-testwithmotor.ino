// Include the required libraries
#include <Arduino.h>

// Define the relay control pin
const int relayPin = 16; // Replace with the actual GPIO pin you are using

void setup() {
  // Initialize the relay pin as an output
  pinMode(relayPin, OUTPUT);
  // Set the relay to its initial state (off)
  digitalWrite(relayPin, HIGH);
}

void loop() {
  // Turn the motor on for 2 seconds
  digitalWrite(relayPin, HIGH);
  delay(2000); // 2 seconds

  // Turn the motor off for 2 seconds
  //digitalWrite(relayPin, LOW);
  //delay(2000); // 2 seconds
}
