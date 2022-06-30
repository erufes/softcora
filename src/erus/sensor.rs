use super::erus_types::sensor_gpio;

pub struct Sensor {
    last_reading: u16,
    pin: sensor_gpio::GenericSensorPin,
}

impl Sensor {
    pub fn new(pin: sensor_gpio::GenericSensorPin) -> Self {
        Sensor {
            last_reading: 0,
            pin,
        }
    }
}
