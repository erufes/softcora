#ifndef TIMER_H
#define TIMER_H

#include "../../include/sharedTypes.h"

class Timer {
  public:
    Timer();
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