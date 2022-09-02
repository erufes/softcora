#include "timer.h"

Timer::Timer(uint duration) {
    this->duration = duration;
    this->elapsedTime = 0;
    this->isRunning = false;
    this->done = false;
}
Timer::Timer(uint duration, std::function<void()> callback) : Timer(duration) {
    this->callback = callback;
}
void Timer::start() {
    this->isRunning = true;
    this->startTime = esp_timer_get_time();
}
void Timer::stop() {
    this->isRunning = false;
    this->elapsedTime = esp_timer_get_time() - startTime;
}
void Timer::reset() {
    this->startTime = esp_timer_get_time() - elapsedTime;
    this->done = false;
    this->elapsedTime = 0;
}

void Timer::onFinish(std::function<void()> callback) {
    if(isDone()){
        if(callback != NULL)callback();
    }
}

bool Timer::isDone() {
    return this->done;
}

void Timer::tick() {
    if ((esp_timer_get_time() - startTime) > duration-elapsedTime){
        done = true;
    }
}

void Timer::setDuration(uint duration) {
    this->duration = duration;
}
uint Timer::getDuration() {
    return duration;
}
uint Timer::getRemainingTime() {
    return this->duration - getElapsedTime();
}
uint Timer::getElapsedTime() {
    return (esp_timer_get_time() - startTime);
}