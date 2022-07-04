use esp_idf_hal::ledc::{config::TimerConfig, Channel, Timer};
use esp_idf_hal::prelude::*;

macro_rules! set_engine_speed {
    ($peripherals:ident, $target_timer:ident, $target_channel:ident, $target_pin:ident, $speed:expr) => {
        let pwm_config: TimerConfig = TimerConfig::default().frequency(25.kHz().into());
        let timer = Timer::new($target_timer, &pwm_config).unwrap();
        let mut channel = Channel::new($target_channel, &timer, $target_pin).unwrap();
        channel
            .set_duty(channel.get_max_duty() * $speed as u32)
            .unwrap();
    };
}

pub fn set_left_engine_speed(speed: u8) {
    let peripherals = Peripherals::take().unwrap();
    let pwm_pin = peripherals.pins.gpio14.into_output().unwrap();
    let target_channel = peripherals.ledc.channel0;
    let target_timer = peripherals.ledc.timer0;

    set_engine_speed!(peripherals, target_timer, target_channel, pwm_pin, speed);
}
pub fn set_right_engine_speed(speed: u8) {
    let peripherals = Peripherals::take().unwrap();
    let pwm_pin = peripherals.pins.gpio26;
    let target_channel = peripherals.ledc.channel1;
    let target_timer = peripherals.ledc.timer1;

    set_engine_speed!(peripherals, target_timer, target_channel, pwm_pin, speed);
}
