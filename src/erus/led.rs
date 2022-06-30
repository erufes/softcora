use embedded_hal::digital::v2::OutputPin;
use esp_idf_hal::gpio::{GpioPin, Output};

pub struct LED {
    pin: GpioPin<Output>,
    state: bool,
}

impl LED {
    pub fn new(pin: GpioPin<Output>) -> Self {
        LED { pin, state: false }
    }

    fn update_pin_output(&mut self) {
        match self.state {
            true => {
                self.pin.set_low().unwrap();
            }
            false => {
                self.pin.set_high().unwrap();
            }
        }
    }
    fn set_state(&mut self, state: bool) {
        self.state = state;
        self.update_pin_output();
    }
}

pub trait LEDTrait {
    fn on(&mut self);
    fn off(&mut self);
    fn toggle(&mut self);
}

impl LEDTrait for LED {
    fn on(&mut self) {
        self.set_state(true);
    }
    fn off(&mut self) {
        self.set_state(false);
    }
    fn toggle(&mut self) {
        self.set_state(!self.state);
    }
}
