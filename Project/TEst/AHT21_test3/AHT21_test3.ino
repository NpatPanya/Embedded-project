#include <AHT21.h> // Include your custom AHT21 library

AHT21 myAHT21; // Create an instance of the AHT21 class

void setup() {
  Serial.begin(115200); // Initialize serial communication
  Wire.begin();       // Initialize the I2C communication

  if (myAHT21.begin()) {
    Serial.println("AHT21 sensor initialized successfully");
  } else {
    Serial.println("AHT21 sensor initialization failed. Check connections.");
  }
}

void loop() {
  if (myAHT21.available()) {
    float temperature = myAHT21.getTemperature(); // Get temperature in Celsius
    float humidity = myAHT21.getHumidity();       // Get relative humidity in percentage
    
    if(temperature !=-99.99 and humidity !=-99.99){

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    }else{
      Serial.print("AHT21 Sensor failed to read");
    }

    //delay(2000); // Wait for a few seconds before the next reading
  } else {
    Serial.println("AHT21 sensor not ready. Please wait for the measurement to complete.");
    //delay(500); // Wait and try again
  }
  delay(1000);
}
