use core::fmt;

use super::erus_types::led_gpio::GPIOParam;
use super::led::{LEDTrait, LED};

pub struct ERUSBot {
    led: LED,
}

impl ERUSBot {
    pub fn new(led_gpio: GPIOParam) -> Self {
        let led = LED::new(led_gpio);
        println!("Created new bot with LED on GPIO 0");
        // let sens = Sensors::new(PackedSensorData {
        //     front_left_pin: led_gpio,
        //     front_right_pin: led_gpio,
        //     front_pin: led_gpio,
        //     left_pin: led_gpio,
        //     right_pin: led_gpio,
        // });
        ERUSBot { led }
    }
}

pub trait ERUSBotTrait {
    fn on(&mut self);
    fn off(&mut self);
    fn toggle(&mut self);
    fn tick(&mut self);
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
    fn tick(&mut self) {
        println!("Tick");
    }
}

impl fmt::Display for ERUSBot {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "ERUSBot")
    }
}
