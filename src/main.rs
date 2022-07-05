use std::thread;
use std::time::Duration;

use embedded_hal::digital::v2::OutputPin;
use esp_idf_hal::gpio::{Gpio1, Gpio2, Output};
use esp_idf_hal::ledc::config::TimerConfig;
use esp_idf_hal::ledc::{Channel, Timer, CHANNEL0, CHANNEL1, TIMER0, TIMER1};
use esp_idf_hal::peripherals::Peripherals;

pub mod erus;
use erus::bot::ERUSBot;

use crate::erus::bot::ERUSBotTrait;
use esp_idf_hal::prelude::*;

fn init_timers(timer0: TIMER0, timer1: TIMER1) -> (Timer<TIMER0>, Timer<TIMER1>) {
    let pwm_config: TimerConfig = TimerConfig::default().frequency(25.kHz().into());
    let timer0 = Timer::new(timer0, &pwm_config).unwrap();
    let timer1 = Timer::new(timer1, &pwm_config).unwrap();
    (timer0, timer1)
}

fn init_channels(
    channel0: CHANNEL0,
    channel1: CHANNEL1,
    timer0: Box<Timer<TIMER0>>,
    timer1: Box<Timer<TIMER1>>,
    gpio1: Gpio1<Output>,
    gpio2: Gpio2<Output>,
) -> (
    Channel<CHANNEL0, TIMER0, Box<Timer<TIMER0>>, Gpio1<Output>>,
    Channel<CHANNEL1, TIMER1, Box<Timer<TIMER1>>, Gpio2<Output>>,
) {
    let channel0 = Channel::new(channel0, timer0, gpio1).unwrap();
    let channel1 = Channel::new(channel1, timer1, gpio2).unwrap();
    (channel0, channel1)
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    esp_idf_sys::link_patches();

    let peripherals = Peripherals::take().unwrap();
    let (timer0, timer1) = init_timers(peripherals.ledc.timer0, peripherals.ledc.timer1);
    let (_channel0, _channel1) = init_channels(
        peripherals.ledc.channel0,
        peripherals.ledc.channel1,
        Box::new(timer0),
        Box::new(timer1),
        peripherals.pins.gpio1.into_output().unwrap(),
        peripherals.pins.gpio2.into_output().unwrap(),
    );
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
