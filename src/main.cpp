#include <Arduino.h>

#include "bot.h"
#include "pins.h"

static ERUSBot bot =
    ERUSBot(Pins::engineLeftPin, Pins::engineRightPin, Pins::sensorPins);

void setup() {}

void loop() {
  bot.debug();
  bot.tick();
}
