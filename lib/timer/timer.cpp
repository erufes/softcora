#include "timer.h"

Timer::Timer(uint duration) {}
Timer::Timer(uint duration, std::function<void()> callback) {}
void Timer::start() {}
void Timer::stop() {}
void Timer::reset() {}
void Timer::onFinish(std::function<void()> callback) {}
bool Timer::isDone() {}
void Timer::tick() {}
void Timer::setDuration(uint duration) {}
uint Timer::getDuration() {}
uint Timer::getRemainingTime() {}
uint Timer::getElapsedTime() {}