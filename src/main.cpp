#include <Arduino.h>

#include "AsyncUDP.h"

#include "bot.h"
#include "net.h"
#include "pins.h"
#include "secrets.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <iostream>
#include <memory.h>
#include <time.h>

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(new ERUSBot());

Connection* c;

static int64_t lastTime;

static constexpr int64_t SECONDS = 1000000;

void setup() {
    lastTime = esp_timer_get_time();
    // Connection::setupWirelessConnection();
    // c = new Connection("192.168.0.125", 20002);
}

static int64_t currentTime;
static int64_t timeout = 1024;

int dirFlags = 0;

void nextFlag() { dirFlags = (dirFlags + 1) % 4; }

// static Sensor s = Sensor(32);

void loop() {
    // Motor testing
    {
        Engine* mot1 = bot->getMotor1();
        Engine* mot2 = bot->getMotor2();

        currentTime = esp_timer_get_time();
        int64_t deltaTime = currentTime - lastTime;
        if (deltaTime > 0.2 * SECONDS) {
            lastTime = currentTime;
            nextFlag();
            printf("battery reads %.2f\n", bot->getBatteryVoltage());
            printf("raw battery reads %d\n", bot->getRawBatteryVoltage());

            switch (dirFlags) {
            case 0:
                // printf("setting speed to 0\n");
                mot1->setSpeed(0);
                mot2->setSpeed(0);
                break;
            case 1:
                // printf("setting speed to 255\n");
                mot1->setSpeed(255);
                mot2->setSpeed(255);
                break;
            case 2:
                // printf("setting speed to -255\n");
                mot1->setSpeed(-255);
                mot2->setSpeed(-255);
                break;
            case 3:
                // printf("setting speed to 100\n");
                mot1->setSpeed(100);
                mot2->setSpeed(100);
                break;
            }
        }
    }

    bot->tick();
}
