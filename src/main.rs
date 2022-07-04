use std::thread;
use std::time::Duration;

use embedded_hal::digital::v2::OutputPin;
use esp_idf_hal::peripherals::Peripherals;

pub mod erus;
use erus::bot::ERUSBot;
use esp_idf_hal::ledc::{config::TimerConfig, Channel, Timer};
use esp_idf_hal::prelude::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    esp_idf_sys::link_patches();

    let peripherals = Peripherals::take().unwrap();
    let mut led = peripherals.pins.gpio4.into_output()?;

    let pwm_pin = peripherals.pins.gpio14;
    let pwm_intensity = 3 / 4;

    let bot = ERUSBot::new(peripherals.pins.gpio0.into_output()?.degrade());

    {
        let pwm_config = TimerConfig::default().frequency(25.kHz().into());
        let timer = Timer::new(peripherals.ledc.timer0, &pwm_config)?;
        let mut channel = Channel::new(peripherals.ledc.channel0, &timer, pwm_pin).unwrap();
        let max_duty = channel.get_max_duty();
        channel.set_duty(max_duty * pwm_intensity)?;
    }

    // PWM Setup
    println!("{}", bot);

    loop {
        led.set_high()?;
        // we are using thread::sleep here to make sure the watchdog isn't triggered
        thread::sleep(Duration::from_millis(1000));

        led.set_low()?;
        thread::sleep(Duration::from_millis(1000));
    }
}
