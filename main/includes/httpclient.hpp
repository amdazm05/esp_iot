#ifndef _HTTPCLIENT
#define _HTTPCLIENT

#include "env/env.hpp"
#include "env/cert/pem_cert.hpp"
#include "utils/util.hpp"

class HTTPApiClient
{
    public:
        HTTPApiClient();
        static void HTTPClient_init();
        static void PostPacketToApi(std::string json, const char *  URL);
        static void GetHttpRequestsTask(void);
    private:
        static esp_http_client_config_t httpClientConfig;
        static esp_http_client_handle_t client;
};

#endif //_HTTPCLIENT