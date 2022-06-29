use crate::erus::erus_types::led::{GPIOParam, GPIO};
use embedded_hal::digital::v2::OutputPin;

pub struct LED {
    pin: GPIO,
    state: bool,
}

impl LED {
    pub fn new(pin: GPIOParam) -> Self {
        let output_pin = pin.into_output();

        match output_pin {
            Ok(pin) => LED { pin, state: false },
            Err(_) => panic!("Failed to create LED"),
        }
    }

    fn update_pin_output(&mut self) {
        match self.state {
            true => {
                let res = self.pin.set_low();
                match res {
                    Ok(_) => {}
                    Err(_) => {
                        panic!("Failed to set LED gpio low");
                    }
                }
            }
            false => {
                let res = self.pin.set_high();
                match res {
                    Ok(_) => {}
                    Err(_) => {
                        panic!("Failed to set LED gpio high");
                    }
                }
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
