#include "softapwificonfiguration.hpp"
#include "httpserver.hpp"
#include "stawifimode.hpp"
#include "storagenvshandler.hpp"
#include "sensorscheduler.hpp"

extern "C" 
{
  void app_main(void)
  {
      // Anable security sensor
      char SSID[32]= "ahmedazeem";
      char PWD[64]= "abcdefghi";
      
      StorageHandler::init();
      StorageHandler * storagehandle =  StorageHandler::get_instance();
      // NVS init
      ESP_ERROR_CHECK(esp_event_loop_create_default());
      ESP_ERROR_CHECK(esp_netif_init());

      stawifimode::wifi_scan();
      Http_Server Server(9000);
      WifiConfigurator Configuration(SSID,PWD,&Http_Server::startHttpServer,&Http_Server::stopHttpServer);
      uriMethodHandlerCallback =  &stawifimode::switch_to_sta_mode;
      Configuration.StartConfigurationTask();

      i2c_init(I2C_BUS, I2C_SCL_PIN, I2C_SDA_PIN, I2C_FREQ);
      SensorScheduler SensorSchedulerHandle;
      // Task creations
      xTaskCreate(&SensorScheduler::bme_680_polling_task, "bme_680_task", 2048, NULL, 2, NULL);
      xTaskCreate(&stawifimode::wifi_sta_connected_task, "check_connection_task", 2048, NULL, 4, NULL);
  }

}