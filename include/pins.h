#ifndef PINS_H
#define PINS_H

#include "utils.h"

/*
 * M1 = Left Engine
 * M2 = Right Engine
 */

namespace Pins {

    namespace Engine {

        namespace M1 {
            const uint Power = 25;
            namespace Direction {
                const uint DirA = 26;
                const uint DirB = 27;
            }
        }

        namespace M2 {
            const uint Power = 16;
            namespace Direction {
                const uint DirA = 17;
                const uint DirB = 18;
            }
        }

        static constexpr uint enable = 23;
        static constexpr uint fault = 4;
    }

    namespace i2c {
        static constexpr uint i2cA = 0;
        // static constexpr uint i2cA = 39;
        static constexpr uint i2cB = 42;
    }

    static constexpr uint sensors[5] = {11, 12, 13, 10, 5};

    namespace Buttons {
        static constexpr uint btn1 = 24;
        static constexpr uint btn2 = 20;
    }

    namespace LEDs {
        static constexpr uint led1 = 34;
        static constexpr uint led2 = 38;
    }

    static constexpr uint battery = 39;

}

#endif // PINS_H