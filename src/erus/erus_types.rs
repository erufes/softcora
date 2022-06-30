pub mod led_gpio {
    use esp_idf_hal::gpio::Gpio0;
    use esp_idf_hal::gpio::Output;
    use esp_idf_hal::gpio::Unknown;

    pub type GPIOParam = Gpio0<Unknown>;
    pub type GPIO = Gpio0<Output>;
}

pub mod sensor_gpio {
    use esp_idf_hal::gpio::Gpio2;
    use esp_idf_hal::gpio::Gpio34;
    use esp_idf_hal::gpio::Gpio36;
    use esp_idf_hal::gpio::Gpio39;
    use esp_idf_hal::gpio::Gpio4;
    use esp_idf_hal::gpio::Input;

    pub type Front = Gpio4<Input>;

    pub type FrontLeft = Gpio2<Input>;

    pub type FrontRight = Gpio36<Input>;

    pub type Left = Gpio39<Input>;

    pub type Right = Gpio34<Input>;

    pub enum GenericSensorPin {
        Front,
        Left,
        Right,
        FrontLeft,
        FrontRight,
    }
}

// ADC Pins: GPIO 4, 2, 15, 36
