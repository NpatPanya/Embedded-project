#define RELAY_PIN 16

void setup() {
  pinMode(RELAY_PIN, OUTPUT); // Set the relay pin (GPIO16) as an output
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH); // Turn the relay on (assuming it's active LOW)
  delay(1000); // Wait for 1 second
  digitalWrite(RELAY_PIN, LOW); // Turn the relay off
  delay(1000); // Wait for 1 second
}
