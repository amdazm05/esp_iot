#ifndef __SOFTAP
#define __SOFTAP
#include "util.hpp"
#include "stawifimode.hpp"
// Defines 
#define EXAMPLE_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD

class WifiConfigurator
{
    static constexpr char *TAG = "wifi softAP";
    public:
        WifiConfigurator( char * SSID ,  char * PWD, void (*serverOnstartHandler)(), void (*serverdisconnectHandler)());
        void StartConfigurationTask() ;
        static void ConfigurationTask(void *arg);
        static void wifi_event_handler
        (   
            void* arg, 
            esp_event_base_t event_base,
            int32_t event_id, 
            void* event_data
        ); 
        // static esp_netif_t * p_netif;
    private:
        // For anything that might come 
        static void (*wifievenHandlerStart)();
        static void (*wifievenHandlerStop)();
        char * SSID;
        char * PWD;
        static wifi_config_t wifi_config;
        static wifi_init_config_t cfg;
};

// Reading article for HTTP server
//https://esp32.com/viewtopic.php?t=9687 
#endif //__SOFTAP