#include <Wire.h>

#define AHT21_I2C_ADDR 0x38

class AHT21 {
public:
  AHT21() {}

  bool begin() {
    Wire.begin();
    return true;
  }

  bool readData(float& temperature, float& humidity) {
    Wire.beginTransmission(AHT21_I2C_ADDR);
    Wire.write(0xAC); // Start measurement command
    Wire.endTransmission();

    delay(100); // Wait for measurement completion

    Wire.beginTransmission(AHT21_I2C_ADDR);
    Wire.write(0x33); // Read data command
    Wire.endTransmission();

    delay(10); // Delay for data retrieval

    Wire.requestFrom(AHT21_I2C_ADDR, 6);
    if (Wire.available() == 6) {
      uint8_t data[6];
      for (int i = 0; i < 6; i++) {
        data[i] = Wire.read();
      }

      // Parse the data
      humidity = (float)((data[1] << 8 | data[2]) & 0x3FFF) / 16384.0 * 100.0;
      temperature = (float)(((data[3] << 8 | data[4]) >> 2) / 16384.0 * 165.0 - 40.0);
      
      return true;
    }
    
    return false;
  }
};

AHT21 aht21;

void setup() {
  Serial.begin(115200);
  
  if (aht21.begin()) {
    Serial.println("AHT21 sensor initialized");
  } else {
    Serial.println("AHT21 sensor initialization failed");
  }
}

void loop() {
  float temperature, humidity;

  if (aht21.readData(temperature, humidity)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read data from AHT21");
  }

  delay(2000); // Delay between measurements
}
