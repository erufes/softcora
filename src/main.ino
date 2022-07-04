#include "libs/sensor/sensor.h"
#include <Arduino.h>

#include "libs/bot/bot.h"

static ERUSBot bot = ERUSBot();

void setup() { pinMode(3, OUTPUT); }

void loop() { bot.tick(); }
