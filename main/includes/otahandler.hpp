#ifndef _OTA_UPDATES
#define _OTA_UPDATES

#include "utils/util.hpp"

class OTAHandler
{
    public:
        static void init();
        static OTAHandler * get_instance();
        static void ota_task(void *);
        static esp_err_t validate_image_header(esp_app_desc_t *new_updatedfirmware_info);
    private:
        OTAHandler();
        static OTAHandler * _inst;
        // Client shall be required 
        esp_http_client_config_t httpclient_config;
        esp_https_ota_config_t   ota_config;
};

// Reference followed here
// https://github.com/espressif/esp-idf/blob/master/examples/system/ota/advanced_https_ota/main/advanced_https_ota_example.c
#endif //_OTA_UPDATES