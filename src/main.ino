#include "libs/sensor/sensor.h"
#include <Arduino.h>

void setup() { pinMode(3, OUTPUT); }

void loop() {
    Sensor s = Sensor(0);
    s.print();
}
