#include "softapwificonfiguration.hpp"

wifi_config_t WifiConfigurator::wifi_config;
wifi_init_config_t WifiConfigurator::cfg;
void (*WifiConfigurator::wifievenHandlerStart)();
void (*WifiConfigurator::wifievenHandlerStop)();

WifiConfigurator::WifiConfigurator(  char * SSID ,   char * PWD, void (*serverOnstartHandler)(), void (*serverdisconnectHandler)()):
    SSID(SSID) , PWD(PWD) 
{ 
    wifievenHandlerStop = serverdisconnectHandler;
    wifievenHandlerStart = serverOnstartHandler;
    
    memcpy(wifi_config.ap.ssid,SSID,32);
    memcpy(wifi_config.ap.password,PWD,32);
    wifi_config.ap.ssid_len = 8;

    std::cout<<(char *)&wifi_config.ap.password<<std::endl;
    wifi_config.ap.max_connection = 1;
    wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    wifi_config.ap.pmf_cfg.required = false;

    cfg = WIFI_INIT_CONFIG_DEFAULT();           
}

void WifiConfigurator::ConfigurationTask(void *arg)
{
    while(1)
    {
        std::cout<<"Running Task"<<std::endl;
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}


void WifiConfigurator::wifi_event_handler
    (   
        void* arg, 
        esp_event_base_t event_base,
        int32_t event_id, 
        void* event_data
    )
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) 
    {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
        (*(WifiConfigurator::wifievenHandlerStart))();
    } 
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
        (*(WifiConfigurator::wifievenHandlerStop))();
    }
    
}

void WifiConfigurator::StartConfigurationTask()
{
    // xTaskCreate( &WifiConfigurator::ConfigurationTask, "WifiConfigurationTask", 2048, NULL, 5, NULL);   
    // ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &WifiConfigurator::wifi_event_handler,
                                                        NULL,
                                                        NULL));
    
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &WifiConfigurator::wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             SSID, PWD, 13);
}

    // Station/AP-coexistence mode is what I plan todo 