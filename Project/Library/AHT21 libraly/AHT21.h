#include "AHT21.h"

AHT21::AHT21() {
    _address = 0x38; // Default I2C address
}

void AHT21::begin() {
    Wire.begin();
}

float AHT21::readTemperature() {
    Wire.beginTransmission(_address);
    Wire.write(0xAC);
    Wire.write(0x33);
    Wire.endTransmission();

    delay(100);

    Wire.requestFrom(_address, 4);
    if (Wire.available() == 4) {
        uint16_t rawTemp = Wire.read() << 8 | Wire.read();
        float temperature = ((rawTemp & 0xFFFC) / 65536.0) * 200.0 - 50.0;
        return temperature;
    } else {
        return -99.9; // Error reading temperature
    }
}

float AHT21::readHumidity() {
    Wire.beginTransmission(_address);
    Wire.write(0xAC);
    Wire.write(0x33);
    Wire.endTransmission();

    delay(100);

    Wire.requestFrom(_address, 4);
    if (Wire.available() == 4) {
        Wire.read();
        Wire.read();
        uint16_t rawHumidity = (Wire.read() << 8 | Wire.read()) & 0xFFFC;
        float humidity = (rawHumidity / 65536.0) * 100.0;
        return humidity;
    } else {
        return -99.9; // Error reading humidity
    }
}

