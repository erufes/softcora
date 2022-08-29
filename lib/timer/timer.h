#ifndef TIMER_H
#define TIMER_H

#include "../../include/sharedTypes.h"

static constexpr int64_t SECONDS = 1000000;

class Timer {
    uint startTime, duration;
    bool isRunning;
    std::function<void()> callback;

  public:
    Timer(uint duration);
    Timer(uint duration, std::function<void()> callback);
    void start();
    void stop();
    void reset();
    void onFinish(std::function<void()> callback);
    bool isDone();
    void tick();
    void setDuration(uint duration);
    uint getDuration();
    uint getRemainingTime();
    uint getElapsedTime();
};

#endif