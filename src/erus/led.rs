use crate::erus::erus_types;

pub struct LED {
    pin: erus_types::ERUSLedGPIO,
    state: bool,
}

impl LED {
    pub fn new(pin: erus_types::ERUSLedGPIOParam) -> Self {
        let outputPin = pin.into_output();

        if outputPin.is_ok() {
            LED {
                pin: outputPin.unwrap(),
                state: false,
            }
        } else {
            panic!("Failed to set LED gpio as output");
        }
    }
    fn update_pin_output(&mut self) {
        match self.state {
            true => {
                // TODO: handle error!
                self.pin.set_low();
            }
            false => {
                self.pin.set_high();
            }
        }
    }
}

pub trait LEDTrait {
    fn on(&mut self);
    fn off(&mut self);
    fn toggle(&mut self);
}

impl LEDTrait for LED {
    fn on(&mut self) {
        self.state = true;
        self.update_pin_output();
    }
    fn off(&mut self) {
        self.state = false;
        self.update_pin_output();
    }
    fn toggle(&mut self) {
        self.state = !self.state;
        self.update_pin_output();
    }
}
