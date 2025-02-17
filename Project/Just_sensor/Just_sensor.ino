#include <AHT21.h>  // Include your custom AHT21 library
#include "MQUnifiedsensor.h"
#define gaspin 34

// Create an instance of the MQUnifiedsensor class
MQUnifiedsensor mySensor("ESP32", 3.3, 12, gaspin, "MQ-9");  // Assuming 3.3V and 12-bit ADC

AHT21 myAHT21;  // Create an instance of the AHT21 class
bool status;
float ppm = 0;          // Read the sensor and get the gas concentration in PPM
float temperature = 0;  // Get temperature in Celsius
float humidity = 0;




void setup() {
  Serial.begin(115200);  // Initialize serial communication
  Wire.begin(21, 22);    // Specify SDA (GPIO21) and SCL (GPIO22)
                         //Wire.begin();       // Initialize the I2C communication
                         //light.begin(); // inicializes the pin

  //MQ9 section
  mySensor.init();
  // Print sensor information to the serial monitor
  mySensor.serialDebug(true);
  //AHT21 Section
  if (myAHT21.begin()) {
    Serial.println("AHT21 sensor initialized successfully");
  } else {
    Serial.println("AHT21 sensor initialization failed. Check connections.");
  }
}

void loop() {

  if (myAHT21.available()) {
    ppm = mySensor.readSensor();             // Read the sensor and get the gas concentration in PPM
    temperature = myAHT21.getTemperature();  // Get temperature in Celsius
    humidity = myAHT21.getHumidity();        // Get relative humidity in percentage*/

    if (0.00 <= humidity <= 100.00 && -40.00 <= temperature <= 120.00) {

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");

      Serial.print("Gas Concentration (PPM): ");
      Serial.println(ppm);

    } else {
      Serial.println("AHT21 Sensor failed to read");
    }

    delay(1000);  // Wait for a few seconds before the next reading
  } else {
    /*debugged
    status = myAHT21.isBusy();
    Serial.print("AHT21 sensor not ready. Error code: ");
    Serial.println(status);
    */
    Serial.println("AHT21 sensor not ready,please wait.");
  }
  delay(1000);

}
