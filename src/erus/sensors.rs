use super::erus_types::sensor_gpio;
use super::sensor::Sensor;

pub struct Sensors {
    pub front_left: Sensor,
    pub front_right: Sensor,
    pub front: Sensor,
    pub left: Sensor,
    pub right: Sensor,
}

impl Sensors {
    pub fn new(sensor_data: sensor_gpio::PackedSensorData) -> Self {
        let front_left = Sensor::new(sensor_data.front_left_pin);
        let front_right = Sensor::new(sensor_data.front_right_pin);
        let front = Sensor::new(sensor_data.front_pin);
        let left = Sensor::new(sensor_data.left_pin);
        let right = Sensor::new(sensor_data.right_pin);
        Sensors {
            front_left,
            front_right,
            front,
            left,
            right,
        }
    }
}
