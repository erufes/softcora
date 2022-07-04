#ifndef BOT_H
#define BOT_H

#include "../engine/engine.h"
#include <memory>

class ERUSBot {
    std::unique_ptr<Engine> engineLeft;
    std::unique_ptr<Engine> engineRight;

  public:
    ERUSBot();
    void tick();
};

#endif // BOT_H