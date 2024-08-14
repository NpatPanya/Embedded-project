#include <Wire.h>
#include <AHT20.h>


AHT20 aht21;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Specify SDA (GPIO21) and SCL (GPIO22)
  aht21.begin();
}

void loop() {
  float temperature = aht21.getTemperature();
  float humidity = aht21.getHumidity();

  if (temperature != -99.9 && humidity != -99.9) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read from AHT21 sensor.");
  }

  delay(2000); // Read sensor data every 2 seconds
}