// Define the pin to which the MQ-9 sensor is connected (GPIO 34 on ESP32)
const int sensorPin = 34;

void setup() {
  // Initialize serial communication at a baud rate of 9600
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(sensorPin);
  
  // Print the sensor value to the serial monitor
  Serial.print("Analog Value: ");
  Serial.println(sensorValue);

  // You can also convert the analog value to a voltage if you know the reference voltage.
  // For example, if using a 3.3V board (ESP32), you can calculate the voltage like this:
  // float voltage = (sensorValue / 4095.0) * 3.3;
  // Serial.print("Voltage: ");
  // Serial.println(voltage);

  // Add a delay to control the rate of readings (in milliseconds)
  delay(1000); // 1 second
}
