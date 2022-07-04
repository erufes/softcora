#include <Arduino.h>

#include "libs/bot/bot.h"
#include "libs/pins.h"

static ERUSBot bot =
    ERUSBot(Pins::engineLeftPin, Pins::engineRightPin, Pins::sensorPins);

void setup() {}

void loop() {
    bot.debug();
    bot.tick();
    sleep(10);
}
