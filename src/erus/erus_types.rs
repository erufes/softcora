pub mod led_gpio {
    use esp_idf_hal::gpio::Gpio0;
    use esp_idf_hal::gpio::Output;
    use esp_idf_hal::gpio::Unknown;

    pub type GPIOParam = Gpio0<Unknown>;
    pub type GPIO = Gpio0<Output>;
}

pub mod sensor_gpio {
    use esp_idf_hal::gpio::Gpio0;
    use esp_idf_hal::gpio::Input;
    use esp_idf_hal::gpio::Unknown;

    pub struct PackedSensorData {
        pub front_pin: FrontParam,
        pub left_pin: LeftParam,
        pub right_pin: RightParam,
        pub front_left_pin: FrontLeftParam,
        pub front_right_pin: FrontRightParam,
    }

    pub type FrontParam = Gpio0<Unknown>;
    pub type Front = Gpio0<Input>;

    pub type FrontLeftParam = Gpio0<Unknown>;
    pub type FrontLeft = Gpio0<Input>;

    pub type FrontRightParam = Gpio0<Unknown>;
    pub type FrontRight = Gpio0<Input>;

    pub type LeftParam = Gpio0<Unknown>;
    pub type Left = Gpio0<Input>;

    pub type RightParam = Gpio0<Unknown>;
    pub type Right = Gpio0<Input>;
}
