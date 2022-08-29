#include "sensor.h"
#include <Arduino.h>
#include <stdio.h>

Sensor::Sensor(uint pin) {
    this->pin = pin;
    this->reading = 0;
    printf("Sensor @ pin %d created successfully!\n", pin);
}

std::string Sensor::toString() {
    char str[99];
    sprintf(str, "Sensor %d - %.2f", this->pin, this->reading);
    return std::string(str);
}

void Sensor::tick() {
    this->read();
    // printf("[Sens %d] reading: %.2f\%\n", this->pin, this->reading);
}

void Sensor::calibrate() {}

void Sensor::read() { this->reading = float(analogRead(this->pin)) / 4096; }
