#include <Arduino.h>

#include "bot.h"
#include "pins.h"

static ERUSBot bot = ERUSBot(
    {Pins::Engine::left::power, Pins::Engine::left::direction::forward},
    {Pins::Engine::right::power, Pins::Engine::right::direction::forward},
    Pins::sensors);

void setup() {}

void loop() {
    bot.debug();
    bot.tick();
    delay(10);
}
