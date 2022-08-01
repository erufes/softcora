#include "sensor.h"
#include <Arduino.h>
#include <stdio.h>

Sensor::Sensor(uint pin) {
    this->pin = pin;
    printf("Sensor @ pin %d created successfully!\n", pin);
}

std::string Sensor::toString() { return "all ok!"; }

void Sensor::tick() {
    this->read();
    printf("[Sens %d] reading: %.2f\%\n", this->pin, this->reading);
}

void Sensor::calibrate() {}

void Sensor::read(unsigned char readMode) {
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, HIGH);
    delayMicroseconds(15);
    int64_t now = esp_timer_get_time();
    pinMode(this->pin, INPUT);
    while (1) {
        if (digitalRead(this->pin) == LOW ||
            esp_timer_get_time() - now > TIMEOUT)
            break;
    }
    int64_t diff = esp_timer_get_time() - now;
    float percent = float(diff) / TIMEOUT;
    printf("[%d] diff: %.2f\%\n", this->pin, percent);
}

void Sensor::emitterOn() {
    if (emitterDDR == 0)
        return;
    *emitterDDR |= emitterBitmask;
    *emitterPORT |= emitterBitmask;
    delayMicroseconds(200);
}

void Sensor::emitterOff() {
    if (emitterDDR == 0)
        return;
    *emitterDDR |= emitterBitmask;
    *emitterPORT &= ~emitterBitmask;
    delayMicroseconds(200);
}