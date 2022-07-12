#include <Arduino.h>

#include "bot.h"
#include "pins.h"

static ERUSBot bot = ERUSBot(
    {Pins::Engine::left::power, Pins::Engine::left::direction::forward,
     Pins::Engine::left::direction::backward},
    {Pins::Engine::right::power, Pins::Engine::right::direction::forward,
     Pins::Engine::right::direction::backward},
    Pins::sensors);

void setup() {}

void loop() {
    bot.debug();
    bot.tick();
    delay(10);
}
