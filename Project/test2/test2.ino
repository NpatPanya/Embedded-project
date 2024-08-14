#include <AHT21.h>  // Include your custom AHT21 library
#include "MQUnifiedsensor.h"
#include "Relay.h"
#define gaspin 34
Relay light(16, false);  // constructor receives (pin, isNormallyOpen) true = Normally Open, false = Normally Closed

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
  light.begin();  // inicializes the pin

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

    if (0.00 >= humidity >= 100.00 && -40.00 >= temperature >= 120.00) {
      Serial.println("AHT21 Sensor failed to read");

      //Wire.endTransmission() == 1;
    } else {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");

      Serial.print("Gas Concentration (PPM): ");
      Serial.println(ppm);
      if (temperature >= 28.00) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        Serial.print("Gas Concentration (PPM): ");
        Serial.println(ppm);
        light.turnOn();
      }
    }

  } else {
    /*debugged
    status = myAHT21.isBusy();
    Serial.print("AHT21 sensor not ready. Error code: ");
    Serial.println(status);
    */
    Serial.println("AHT21 sensor not ready,please wait.");

    delay(1000);  // Wait for a few seconds before the next reading
  }
  bool isLightOn = light.getState(); //returns a bool, true = on, false = off
  // Read the sensor and get the gas concentration in PPM
  //float ppm = mySensor.readSensor();

  // Print the gas concentration to the serial monitor
  //Serial.print("Gas Concentration (PPM): ");
  //Serial.println(ppm);

  //delay(1000); // Delay for one second
}
