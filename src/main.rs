use std::thread;
use std::time::Duration;

use embedded_hal::digital::v2::OutputPin;
use esp_idf_hal::peripherals::Peripherals;

pub mod erus;
use erus::bot::ERUSBot;

use crate::erus::bot::ERUSBotTrait;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    esp_idf_sys::link_patches();

    let peripherals = Peripherals::take().unwrap();
    let mut led = peripherals.pins.gpio4.into_output()?;

    let mut bot = ERUSBot::new(peripherals.pins.gpio0.into_output()?.degrade());
    println!("{}", bot);

    bot.go_backward(12);
    bot.go_forward(12);

    loop {
        led.set_high()?;
        // we are using thread::sleep here to make sure the watchdog isn't triggered
        thread::sleep(Duration::from_millis(1000));

        led.set_low()?;
        thread::sleep(Duration::from_millis(1000));
    }
}
