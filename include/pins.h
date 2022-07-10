#ifndef PINS_H
#define PINS_H

#include "utils.h"

/*
 * M1 = Left Engine
 * M2 = Right Engine
 */

namespace Pins {

    namespace Engine {

        namespace left {
            const uint power = 25;
            const uint direction = 27;
            // ??? = 35;
        }

        namespace right {
            const uint power = 14;
            const uint direction = 15;
            // ??? = 16;
        }

        static constexpr uint enable = 36;
    }

    namespace i2c {
        static constexpr uint unk1 = 39;
        static constexpr uint unk2 = 42;
    }

    static constexpr uint sensors[5] = {12, 13, 10, 11, 5};

    namespace Buttons {
        static constexpr uint btn1 = 24;
        static constexpr uint btn2 = 20;
    }

    namespace LEDs {
        static constexpr uint led1 = 34;
        static constexpr uint led2 = 38;
    }

}

#endif // PINS_H