use crate::erus::led::{LEDTrait, LED};
use esp_idf_hal::gpio::{self, Unknown};

use super::erus_types;
pub struct ERUSBot {
    led: LED,
}

impl ERUSBot {
    pub fn new(led_gpio: erus_types::ERUSLedGPIOParam) -> Self {
        let led = LED::new(led_gpio);
        unimplemented!("ERUSBot::new");
        // ERUSBot { led }
    }
}

pub trait ERUSBotTrait {
    fn on(&mut self);
    fn off(&mut self);
    fn toggle(&mut self);
}

impl ERUSBotTrait for ERUSBot {
    fn on(&mut self) {
        self.led.on();
    }
    fn off(&mut self) {
        self.led.off();
    }
    fn toggle(&mut self) {
        self.led.toggle();
    }
}
