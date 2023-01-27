#ifndef _STAWIFIMODE
#define _STAWIFIMODE

#include "util.hpp"

class stawifimode
{
private:
    /* data */
    static std::vector<std::string> listofSSIDscan;
    static uint8_t s_retry_num;
    static EventGroupHandle_t s_wifi_event_group;
    static wifi_mode_t current_mode;
public:
    stawifimode(/* args */);
    
    static std::vector<std::string>& get_list_of_ssids();
    static void wifi_scan();
    static void switch_to_sta_mode(std::string & ssid, std::string & password);
    static void stamode_event_handler
    (     
        void* arg, esp_event_base_t event_base,
        int32_t event_id, 
        void* event_data
    );
    static void wifi_sta_connected_task(void *params);

    ~stawifimode();
};

#endif //_STAWIFIMODE