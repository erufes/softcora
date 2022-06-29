use std::thread;
use std::time::Duration;

use embedded_hal::digital::v2::OutputPin;
use esp_idf_hal::peripherals::Peripherals;

mod erus;
#[cfg(no_unused_variables)]
use erus::bot::ERUSBot;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    esp_idf_sys::link_patches();

    #[cfg(no_unused_variables)]
    let bot = ERUSBot::new(0);

    let peripherals = Peripherals::take().unwrap();
    let mut led = peripherals.pins.gpio4.into_output()?;

    loop {
        led.set_high()?;
        // we are using thread::sleep here to make sure the watchdog isn't triggered
        thread::sleep(Duration::from_millis(1000));

        led.set_low()?;
        thread::sleep(Duration::from_millis(1000));
    }
}
