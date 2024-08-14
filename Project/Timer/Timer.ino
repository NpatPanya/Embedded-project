#include <AHT21.h>
#include "MQUnifiedsensor.h"
#include "Relay.h"

#define gaspin 34
Relay light(16, false); // constructor receives (pin, isNormallyOpen) true = Normally Open, false = Normally Closed

MQUnifiedsensor mySensor("ESP32", 3.3, 12, gaspin, "MQ-9");
AHT21 myAHT21;
bool status;
float ppm = 0;
float temperature = 0;
float humidity = 0;

volatile bool readSensorsFlag = false;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  readSensorsFlag = true;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  light.begin(); // initializes the pin

  mySensor.init();
  mySensor.serialDebug(true);

  if (myAHT21.begin()) {
    Serial.println("AHT21 sensor initialized successfully");
  } else {
    Serial.println("AHT21 sensor initialization failed. Check connections.");
  }

  // Configure the hardware timer to call the onTimer function every 10 seconds (adjust as needed)
  timer = timerBegin(0, 80, true); // Timer 0, divider 80 (1 MHz clock)
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 10000000, true); // 10 seconds interval
  timerAlarmEnable(timer);
}

void loop() {
  if (!readSensorsFlag) {
    Serial.println("Senssor not avalable.");
    
  }
  else{
     // Read MQ9 and AHT21 sensors
    ppm = mySensor.readSensor();
    temperature = myAHT21.getTemperature();
    humidity = myAHT21.getHumidity();

    if (100.00 <= humidity && humidity <= 00.00 && 120.00 <= temperature && temperature <= -40.00) {
      Serial.println("Can't measure data out of range.")
     

    }else{ 
      if(humidity >= 0.00 and humidity <=100.00 and temperature >=-40.00 and temperature <=120.00){


    // Display sensor data in Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Gas Concentration (PPM): ");
    Serial.println(ppm);
    light.turnOff(); // turns relay off

    // Reset the flag
    readSensorsFlag = false;
      }
      else{
      }
      
    }
   
  }

  if (0.00 <= humidity && humidity <= 100.00 && -40.00 <= temperature && temperature <= 120.00) {
    // Your code for normal temperature and humidity conditions
  } else if (temperature >= 41.00 && humidity <= 40.00) {
    // Your code for high temperature and low humidity conditions
  }
  // Your other code can go here

  switch(choose){
    case 1:
    break;
    case 2:
    break;
    case 3:
    break;
  }
}
