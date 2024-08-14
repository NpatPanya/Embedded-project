#include <AHT21.h>  // Include your custom AHT21 library
#include "MQUnifiedsensor.h"
#include "Relay.h"
#define gaspin 34
#define RELAY_PIN 16  // กำหนดขาที่เชื่อมต่อกับโมเตอร์
#define OPEN_TEMPERATURE 41.00  // กำหนดอุณหภูมิที่เปิดโมเตอร์
#define LOW_HUMIDITY 40.00     // กำหนดความชื้นที่ต้องการให้น้อยกว่าเพื่อเปิดโมเตอร์
//Relay light(16, false);  // constructor receives (pin, isNormallyOpen) true = Normally Open, false = Normally Closed

// Create an instance of the MQUnifiedsensor class
MQUnifiedsensor mySensor("ESP32", 3.3, 12, gaspin, "MQ-9");  // Assuming 3.3V and 12-bit ADC

AHT21 myAHT21;  // Create an instance of the AHT21 class
bool status;
float ppm = 0;          // Read the sensor and get the gas concentration in PPM
float temperature = 0;  // Get temperature in Celsius
float humidity = 0;

bool readSensorsFlag = true;




void setup() {
  Serial.begin(115200);  // Initialize serial communication
  Wire.begin(21, 22);    // Specify SDA (GPIO21) and SCL (GPIO22)
  //Wire.begin();       // Initialize the I2C communication
  //light.begin();  // inicializes the pin

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
  if (readSensorsFlag) {
    ppm = mySensor.readSensor();             // อ่านค่า PPM จากเซนเซอร์
    temperature = myAHT21.getTemperature();  // อ่านอุณหภูมิใน Celsius
    humidity = myAHT21.getHumidity();        // อ่านค่าความชื้นสัมพัทธ์ในเปอร์เซ็นต์

    if (humidity >= 0.00 && humidity <= 100.00 && temperature >= -40.00 && temperature <= 120.00) {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");

      Serial.print("Gas Concentration (PPM): ");
      Serial.println(ppm);

      // เช็คเงื่อนไขเพื่อเปิดหรือปิดโมเตอร์
      if (temperature >= OPEN_TEMPERATURE && humidity <= LOW_HUMIDITY) {
        // เปิดโมเตอร์
        digitalWrite(RELAY_PIN, HIGH);
      } else {
        // ปิดโมเตอร์
        digitalWrite(RELAY_PIN, LOW);
      }
    } else {
      Serial.println("Invalid temperature or humidity values.");
    }
  } else {
    Serial.println("AHT21 Sensor failed to read.");
  }

  delay(1000);  // รอเวลาสักครู่ก่อนอ่านข้อมูลใหม่
}