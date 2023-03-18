#ifndef URI_HANDLERS
#define URI_HANDLERS

#include "util.hpp"
#include "wificonfigurationhtml.h"
// Custom utils
#include "uri/uritokenstructures.hpp"
#include "uri/uriutility.hpp"
#include "stawifimode.hpp"
#include "softapwificonfiguration.hpp"

static std::vector<Token> TokenVector = {};

// this function pointer points to method used for passing values obtained from the handler and do something
static void (*uriMethodHandlerCallback)(std::string & value1, std::string &value2)= nullptr;

static esp_err_t methodHandler(httpd_req_t* httpRequest)
{
   wifiConfigurationHTMLString = std::string(wifiConfigurationHTML);
    ESP_LOGI("HTTP_URIHANDLERS_TAG","This is the handler for the <%s> URI", httpRequest->uri);
    std::vector<std::string> token = {};
    seperate_token_from_uri((char *)httpRequest->uri,token);
    split_token_key_value_serialise(token,TokenVector);
    std::vector<std::string> strings = stawifimode::get_list_of_ssids();
    addScansToHtml(strings);
    if(TokenVector.size()>0)
    {
        stawifimode::switch_to_sta_mode(TokenVector[0].value,TokenVector[1].value);
        ESP_LOGI("HTTP_URIHANDLERS_TAG","SSID  %s - %s", TokenVector[0].key.data(),TokenVector[0].value.data());
        ESP_LOGI("HTTP_URIHANDLERS_TAG","PASS  %s - %s", TokenVector[1].key.data(),TokenVector[1].value.data());
        ESP_LOGI("HTTP_URIHANDLERS_TAG","EMAIL  %s - %s", TokenVector[2].key.data(),TokenVector[2].value.data());
    }

    httpd_resp_send(httpRequest,wifiConfigurationHTML,HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t readSSIDHandler(httpd_req_t* httpRequest)
{
    ESP_LOGI("HTTP_URIHANDLERS_TAG","SSID handler for the <%s> URI", httpRequest->uri);
    return ESP_OK;
}

static esp_err_t readPasswordHandler(httpd_req_t* httpRequest)
{
    ESP_LOGI("HTTP_URIHANDLERS_TAG","Password handler for the <%s> URI", httpRequest->uri);
    return ESP_OK;
}

#endif //URI_HANDLERS