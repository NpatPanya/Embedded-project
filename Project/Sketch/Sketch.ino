#include <AHT21.h>
#include "MQUnifiedsensor.h>
#define RelayPin 16 // Pin connected to the relay module
#define gaspin 34  // Pin MQ9
#define HUMIDITY_LIMIT 80.0     // Set the humidity safety limit
#define TEMPERATURE_LIMIT 40.0 // Set the temperature safety limit
#define GAS_LIMIT 100.0        // Set the gas concentration safety limit

MQUnifiedsensor mySensor("ESP32", 3.3, 12, gaspin, "MQ-9");
AHT21 myAHT21;

bool status;
float ppm = 0;
float temperature = 0;
float humidity = 0;

hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer() {
  // Call the function to check sensor values and control the relay
  checkSensorValues();
}

void checkSensorValues() { //ตัวควบคุม Relay
  ppm = mySensor.readSensor();
  temperature = myAHT21.getTemperature();
  humidity = myAHT21.getHumidity();

  if (humidity >= HUMIDITY_LIMIT || temperature >= TEMPERATURE_LIMIT || ppm >= GAS_LIMIT) {
    // Exceeded safety limits, turn on the relay
    digitalWrite(RelayPin, HIGH);
  } else {
    // Within safety limits, turn off the relay
    digitalWrite(RelayPin, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); //Pin SCL SDK ของ AHT21

  mySensor.init();
  mySensor.serialDebug(true);

  if (myAHT21.begin()) {
    Serial.println("AHT21 sensor initialized successfully");
  } else {
    Serial.println("AHT21 sensor initialization failed. Check connections.");
  }

  pinMode(RelayPin, OUTPUT); // Set relayPin as an output
  digitalWrite(RelayPin, LOW); // Initialize the relay to be off

  timer = timerBegin(0, 80); // Use timer 0, prescaler 80 for 1us resolution
  timerAttachInterrupt(timer, &onTimer, true); // Attach the interrupt
  timerAlarmWrite(timer, 1000000, true); // Set the alarm to trigger every 1 second
  timerAlarmEnable(timer); // Enable the timer
}

void loop() {
  //ใช้millis นับเวลา ทุก 5 วินาที แทน delay
  ppm = mySensor.readSensor();             // Read the sensor and get the gas concentration in PPM
  temperature = myAHT21.getTemperature();  // Get temperature in Celsius
  humidity = myAHT21.getHumidity();        // Get relative humidity in percentage*/

  if (!myAHT21.available()) {
    /*debugged
    status = myAHT21.isBusy();
    Serial.print("AHT21 sensor not ready. Error code: ");
    Serial.println(status);
    */
    Serial.println("AHT21 sensor not ready,please wait.");
    
  } 
  else {
    if (0.00 <= humidity <= 100.00 && -40.00 <= temperature <= 120.00) {

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");

      Serial.print("Gas Concentration (PPM): ");
      Serial.println(ppm);

      //Wire.endTransmission() == 1;
    }
    else {
      Serial.println("Failed! Values exceed sensor measurement.");
    }
  }
}
