#include "sensorscheduler.hpp"
#include "driver/adc.h"

bme680_sensor_t* SensorScheduler::bme_sensor_obj = nullptr;
SensorScheduler::SensorScheduler()
{
  ESP_LOGE("SensorScheduler", "NULL REFERENCE");
  bme_sensor_obj = bme680_init_sensor(I2C_BUS, BME680_I2C_ADDRESS_1, 0);
  // Constructor initialises the sensors params
  if (bme_sensor_obj)
  {
    bme680_set_oversampling_rates(bme_sensor_obj, osr_4x, osr_none, osr_2x);
    bme680_set_filter_size(bme_sensor_obj, iir_size_7);
    bme680_set_heater_profile(bme_sensor_obj, 0, 200, 100);
    bme680_use_heater_profile(bme_sensor_obj, 0);
    bme680_set_ambient_temperature(bme_sensor_obj, 10);
    ESP_LOGI("SensorScheduler", "BME_680 Initialised");
  }
  else
  {
    ESP_LOGI("SensorScheduler", "NULL REFERENCE");
  }

  /*PIR Sensor Routine Will be called here*/
  adc2_config_channel_atten(PIR_PIN, PIR_RES);
}

// Sensor tasks
void SensorScheduler::bme_680_polling_task(void* pvParameters)
{
  bme680_values_float_t values;
  TickType_t last_wakeup = xTaskGetTickCount();
  // as long as sensor configuration isn't changed, duration is constant
  uint32_t duration = bme680_get_measurement_duration(bme_sensor_obj);

  while (1)
  {
    // trigger the sensor to start one TPHG measurement cycle
    if (bme680_force_measurement(bme_sensor_obj))
    {
      vTaskDelay(duration);
      if (bme680_get_results_float(bme_sensor_obj, &values))
        ESP_LOGI("Sensor Scheduler ", "BME680 Sensor: %.2f °C, %.2f %%, %.2f hPa, %.2f Ohm\n",
          values.temperature, values.humidity,
          values.pressure, values.gas_resistance);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void SensorScheduler::pir_polling_task(void* pvParameters)
{
  int value = rand() % 10;

  while (1)
  {
    adc2_get_raw(PIR_PIN, ADC_WIDTH_BIT_12, &value);
    printf("Analog value from IO27: %d\n", value);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

SensorScheduler::~SensorScheduler()
{

}

