use super::erus_types::sensor_gpio;

pub struct Sensor {
    reading: u8,
}

impl Sensor {
    pub fn new(pin: sensor_gpio::FrontParam) -> Self {
        Sensor { reading: 0 }
    }
}
