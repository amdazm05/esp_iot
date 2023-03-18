#ifndef _HTTPCLIENT
#define _HTTPCLIENT

#include "env/env.hpp"
#include "utils/util.hpp"

class HTTPApiClient
{
    public:
        HTTPApiClient();
        static std::string GetPacketFromAPI(const char *);
        static void PostPacketToApi(std::string && json, const char *  URL);
        static esp_err_t _http_event_handle(esp_http_client_event_t *evt);
        static esp_err_t _http_event_handle_write(esp_http_client_event_t *evt);
    private:
        static esp_http_client_config_t httpClientConfigGet;
        static esp_http_client_config_t httpClientConfigPost;
        static esp_http_client_handle_t clientWrite;
        static esp_http_client_handle_t client;
        static char buffer[1<<10];
        static int recievedBytes;
};

#endif //_HTTPCLIENT