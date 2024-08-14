#include "MQUnifiedsensor.h"

// Create an instance of the MQUnifiedsensor class
MQUnifiedsensor mySensor("ESP32", 3.3, 12, 34, "MQ-2"); // Assuming 3.3V and 12-bit ADC

void setup() {
  Serial.begin(9600);

  // Initialize the sensor
  mySensor.init();

  // Optionally, set calibration parameters (R0, RL, a, b, etc.)
  // mySensor.setR0(10);
  // mySensor.setRL(10);
  // mySensor.setA(2.0);
  // mySensor.setB(0.5);
  // mySensor.setRegressionMethod(1); // Use exponential regression

  // Print sensor information to the serial monitor
  mySensor.serialDebug(true);
}

void loop() {
  // Read the sensor and get the gas concentration in PPM
  float ppm = mySensor.readSensor();

  // Print the gas concentration to the serial monitor
  Serial.print("Gas Concentration (PPM): ");
  Serial.println(ppm);

  delay(1000); // Delay for one second
}
