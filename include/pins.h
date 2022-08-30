#ifndef PINS_H
#define PINS_H

#include "sharedTypes.h"
#include "utils.h"

/*
 * M1 = Left Engine
 * M2 = Right Engine
 */

namespace Pins {

    namespace Engine {

        namespace M1 {
            const pinType Power = 25;
            namespace Direction {
                const pinType DirA = 26;
                const pinType DirB = 27;
            }
        }

        namespace M2 {
            const pinType Power = 16;
            namespace Direction {
                const pinType DirA = 17;
                const pinType DirB = 18;
            }
        }

        static constexpr pinType enable = 23;
        static constexpr pinType fault = 4;
    }

    namespace i2c {
        static constexpr pinType i2cA = 0;
        // static constexpr pinType i2cA = 39;
        static constexpr pinType i2cB = 42;
    }

    static constexpr pinType sensors[5] = {32, 33, 34, 35, 36};

    namespace Buttons {
        static constexpr pinType btn1 = 24;
        static constexpr pinType btn2 = 20;
    }

    namespace LEDs {
        static constexpr pinType led1 = 5;
        static constexpr pinType led2 = 19;
    }

    static constexpr pinType battery = 39;

}

#endif // PINS_H