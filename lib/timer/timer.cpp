#include "timer.h"

Timer::Timer(uint duration) {
    this->duration = duration;
    this->elapsedTime = 0;
    this->isRunning = false;
    this->done = false;
}
Timer::Timer(uint duration, std::function<void()> callback) {
    this->duration = duration;
    this->elapsedTime = 0;
    this->isRunning = false;
    this->callback = callback;
    this->done = false;
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
    this->startTime = duration + esp_timer_get_time();
    this->done = false;
}

void Timer::onFinish(std::function<void()> callback) {
    if(isDone()){
        callback();
    }
}

bool Timer::isDone() {
    if(this->done && this->isRunning){
        return true;
    }
    return false;
}

void Timer::tick() {
    if (isRunning && (esp_timer_get_time() - startTime) > duration-elapsedTime){
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