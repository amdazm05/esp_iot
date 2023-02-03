#ifndef     _ENV
#define     _ENV

// This define is required for working with the older version of the BME680 library
#define     CONFIG_FREERTOS_ENABLE_BACKWARD_COMPATIBILITY

// BME 680 i2c configurations
#define     I2C_BUS 0
#define     I2C_SCL_PIN GPIO_NUM_22
#define     I2C_SDA_PIN GPIO_NUM_21
#define     I2C_FREQ I2C_FREQ_100K
#define     PIR_PIN ADC2_CHANNEL_7
#define     PIR_RES ADC_ATTEN_DB_0

#endif
