#include <Arduino.h>

#include "AsyncUDP.h"

#include "bot.h"
#include "net.h"
#include "pins.h"
#include "secrets.h"
#include "timer.h"
#include <iostream>
#include <memory.h>
#include <time.h>

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(new ERUSBot());

Connection* c;

static int64_t lastTime;

static Timer* tempo;

void setup() {
    tempo = new Timer(0.2 * SECONDS);
    tempo->start();
    // Connection::setupWirelessConnection();
    // c = new Connection("192.168.0.125", 20002);
}

static int64_t currentTime;
static int64_t timeout = 1024;

int dirFlags = 0;

void nextFlag() { dirFlags = (dirFlags + 1) % 4; }

void loop() {
    // Motor testing
    {
        Engine* mot1 = bot->getMotor1();
        Engine* mot2 = bot->getMotor2();
        tempo->tick();
        if (tempo->isDone()) {
            tempo->reset();
            // nextFlag();
            // printf("battery reads %.2f\n", bot->getBatteryVoltage());
            // printf("raw battery reads %d\n", bot->getRawBatteryVoltage());
            bot->debug();

            // switch (dirFlags) {
            // case 0:
            //     mot1->setSpeed(0);
            //     mot2->setSpeed(0);
            //     break;
            // case 1:
            //     mot1->setSpeed(255);
            //     mot2->setSpeed(255);
            //     break;
            // case 2:
            //     mot1->setSpeed(-255);
            //     mot2->setSpeed(-255);
            //     break;
            // case 3:
            //     mot1->setSpeed(100);
            //     mot2->setSpeed(100);
            //     break;
            // }
        }
    }

    bot->tick();
}
