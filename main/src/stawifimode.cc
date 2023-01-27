#include "stawifimode.hpp"

#define DEFAULT_SCAN_LIST_SIZE 4
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
wifi_mode_t stawifimode::current_mode = {};
std::vector<std::string> stawifimode::listofSSIDscan = {};
uint8_t stawifimode::s_retry_num =0;
EventGroupHandle_t stawifimode::s_wifi_event_group;

stawifimode::stawifimode()
{

}


static const char *TAG = "scan";

static void print_auth_mode(int authmode)
{
    switch (authmode) {
    case WIFI_AUTH_OPEN:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OPEN");
        break;
    case WIFI_AUTH_OWE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OWE");
        break;
    case WIFI_AUTH_WEP:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WEP");
        break;
    case WIFI_AUTH_WPA_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_PSK");
        break;
    case WIFI_AUTH_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_ENTERPRISE");
        break;
    case WIFI_AUTH_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_PSK");
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK");
        break;
    default:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_UNKNOWN");
        break;
    }
}

static void print_cipher_type(int pairwise_cipher, int group_cipher)
{
    switch (pairwise_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    default:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }

    switch (group_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    default:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }
}

void stawifimode::wifi_scan()
{
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ESP_LOGI("WIFI_STA", "Total APs scanned = %u", ap_count);
    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) 
    {
        // Push SSID into a list
        listofSSIDscan.push_back(std::string((char *)&ap_info[i].ssid));
        ESP_LOGI("WIFI_STA", "SSID \t\t%s", ap_info[i].ssid);
        ESP_LOGI("WIFI_STA", "RSSI \t\t%d", ap_info[i].rssi);
        print_auth_mode(ap_info[i].authmode);
        if (ap_info[i].authmode != WIFI_AUTH_WEP) {
            print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
        }
        ESP_LOGI("WIFI_STA", "Channel \t\t%d\n", ap_info[i].primary);
    }
    esp_wifi_disconnect();
    esp_err_t results = esp_wifi_stop();
    // esp_event_loop_delete_default();
    esp_netif_destroy(sta_netif);
    esp_wifi_scan_stop();
}

std::vector<std::string>& stawifimode::get_list_of_ssids()
{
    return stawifimode::listofSSIDscan;
}


void stawifimode::switch_to_sta_mode(std::string & ssid, std::string & password)
{

    esp_wifi_get_mode(&current_mode);
    if (current_mode != WIFI_MODE_STA) 
    {
        esp_wifi_set_mode(WIFI_MODE_STA);
    }

    wifi_config_t sta_config = {0};
    strcpy((char *)sta_config.sta.ssid, ssid.c_str());
    strcpy((char *)sta_config.sta.password, password.c_str());

    esp_wifi_set_config(WIFI_IF_STA, &sta_config);

    esp_wifi_start();

    // Wait for the STA to connect to the AP
    esp_wifi_connect();

    // Create the esp_netif object
    esp_netif_t *esp_netif = esp_netif_create_default_wifi_sta();
    esp_netif_ip_info_t ip_info;

    
    
}

void stawifimode::wifi_sta_connected_task(void *params)
{
    while(1)
    {
        esp_wifi_get_mode(&current_mode);
        if (current_mode != WIFI_MODE_STA) 
        {
            ESP_LOGI("ESP_STA_MODE_WIFI", "In softap mode, not connected to any access point");
        }
        else
        {
            wifi_ap_record_t ap_info =  {};
            esp_err_t err = esp_wifi_sta_get_ap_info(&ap_info);

            if (err == ESP_OK) 
            {
                ESP_LOGI("ESP_STA_MODE_WIFI","STA is connected to AP: %s", ap_info.ssid);
            } 
            else 
            {
                ESP_LOGE("ESP_STA_MODE_WIFI","STA is not connected to any AP");
            }
        }
        vTaskDelay(30000/portTICK_PERIOD_MS);
    }
        
}


stawifimode::~stawifimode()
{
}

// https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32/api-reference/network/esp_netif.html#_CPPv417esp_netif_destroyP11esp_netif_t