use super::erus_types::sensor_gpio::{Front, FrontLeft, FrontRight, Left, Right};
use super::sensor::Sensor;

pub struct Sensors {
    front_left: Sensor,
    front_right: Sensor,
    front: Sensor,
    left: Sensor,
    right: Sensor,
}

// impl Sensors {
//     pub fn new() -> Self {
//         unimplemented!();
//         Sensors {
//             front_left: (),
//             front_right: (),
//             front: (),
//             left: (),
//             right: (),
//         }
//     }
// }
