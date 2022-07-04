use core::fmt;

use super::engine;
use esp_idf_hal::gpio::{GpioPin, Output};

use super::led::{LEDTrait, LED};

pub struct ERUSBot {
    led: LED,
}

impl ERUSBot {
    pub fn new(led_gpio: GpioPin<Output>) -> Self {
        let led = LED::new(led_gpio);
        println!("Created new bot with LED on GPIO 0");
        ERUSBot { led }
    }
}

pub trait ERUSBotTrait {
    fn on(&mut self);
    fn off(&mut self);
    fn toggle(&mut self);
    fn tick(&mut self);
    fn move_left_wheel(&mut self, speed: u8);
    fn move_right_wheel(&mut self, speed: u8);
    fn go_forward(&mut self, speed: u8);
    fn go_backward(&mut self, speed: u8);
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

    fn move_left_wheel(&mut self, speed: u8) {
        engine::set_left_engine_speed(speed);
        println!("Move left");
    }

    fn move_right_wheel(&mut self, speed: u8) {
        engine::set_right_engine_speed(speed);
        println!("Move right");
    }
    fn go_forward(&mut self, speed: u8) {
        engine::set_left_engine_speed(speed);
        engine::set_right_engine_speed(speed);
        println!("Go forward");
    }

    fn go_backward(&mut self, speed: u8) {
        engine::set_left_engine_speed(speed);
        engine::set_right_engine_speed(speed);
        println!("Go backward");
    }
}

impl fmt::Display for ERUSBot {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "ERUSBot")
    }
}
