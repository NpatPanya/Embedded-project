#include <MyAHT21.h>
#include <MQ9GasSensor.h>
#include <WiFi.h>
#include <WebServer.h>

#define gaspin 34
#define relay 16

const int temperatureThreshold = 50.00;
const int lpgLimit = 100;

unsigned long lasttime1 = 0;

float temperature = 0;
float smoke = 0;
float co = 0;
float lpg = 0;

const char* ssid = "ESP32_TTTT";
const char* password = "123456789";

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

MyAHT21 tempSensor;
MQ9GasSensor gasSensor(34);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  pinMode(16, OUTPUT);
  gasSensor.begin();
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  lpg = gasSensor.readLPG();
  co = gasSensor.readCO();
  smoke = gasSensor.readSmoke();
  temperature = tempSensor.getTemperature();
  if (millis() - lasttime1 >= 2000) {

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Carbonmonoxide: ");
    Serial.print(co);
    Serial.println(" ppm");

    Serial.print("Flamable gas : ");
    Serial.print(lpg);
    Serial.println(" kg/m³");

    lasttime1 = millis();
  }

  checkSafetyConditions(temperature, lpg);
}

void checkSafetyConditions(float temperature, float lpg) {

  if (temperature >= temperatureThreshold || lpg >= lpgLimit) {
    if (temperature >= temperatureThreshold) {
      digitalWrite(relay, LOW);
    }
    if (temperature <= temperatureThreshold) {
      digitalWrite(relay, HIGH);
    }
  } else {
    digitalWrite(relay, HIGH);
  }
}

void handle_OnConnect() {
  float lpg = gasSensor.readLPG();
  float co = gasSensor.readCO();
  float smoke = gasSensor.readSmoke();
  float temperature = tempSensor.getTemperature();
  server.send(200, "text/html", SendHTML(temperature, smoke, co, lpg));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float temperature, float smoke, float co, float lpg) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta http-equiv=\"refresh\" content=\"0.5\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP32</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Smart hydrant</h1>\n";
  ptr += "<h1> </h1>\n";
  ptr += "<h1> </h1>\n";
  if (temperature >= temperatureThreshold || lpg >= lpgLimit) {
    if (lpg >= lpgLimit) {
      ptr += "<h1 style=\"color: red; background-color: yellow;\">Warning</h1>\n";
     ptr += "<p class=\"notification\" style=\"font-size: 18px; color: red; background-color: yellow;\">Flammable gas exceeds the safe limit. Please check your place.</p>\n";

    }

    if (temperature >= temperatureThreshold) {
      ptr += "<h1 style=\"color: red; background-color: yellow;\">Warning</h1>\n";
      ptr += "<p class=\"notification\" style=\"font-size: 18px; color: red; background-color: yellow;\">Fire Detected: Please evacuate immediately.</p>\n";

    }
  }
  ptr += "<h1> </h1>\n";
  ptr += "<h1> </h1>\n";
  ptr += "<h1>Temperature:" + String(temperature) + "<span>&#8451;</span>" + "</h1>\n";
  ptr += "<h1>Smoke:" + String(smoke) + " %</h1>\n";
  ptr += "<h1>Carbonmonoxide:" + String(co) + " ppm</h1>\n";
  ptr += "<h1>LPG:" + String(lpg) + " kg/m^3</h1>\n";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
