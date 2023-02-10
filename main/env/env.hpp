#ifndef     _ENV
#define     _ENV

// This define is required for working with the older version of the BME680 library
#define     CONFIG_FREERTOS_ENABLE_BACKWARD_COMPATIBILITY

// BME 680 i2c configurations
#define     I2C_BUS 0
#define     I2C_SCL_PIN GPIO_NUM_22
#define     I2C_SDA_PIN GPIO_NUM_21
#define     I2C_FREQ I2C_FREQ_100K
#define     ADC1_RES ADC_WIDTH_BIT_12
#define     PIR_PIN ADC1_CHANNEL_6
#define     PIR_ATTEN ADC_ATTEN_DB_0
#define     MW_PIN ADC1_CHANNEL_7
#define     MW_ATTEN ADC_ATTEN_DB_0

#endif
