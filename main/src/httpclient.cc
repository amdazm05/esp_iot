#include "httpclient.hpp"

esp_http_client_config_t HTTPApiClient::httpClientConfig = {0};
esp_http_client_handle_t HTTPApiClient::client={0};

esp_err_t _http_event_handle(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_ON_HEADER");
            printf("\n %.*s \n", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                printf("\n %.*s \n", evt->data_len, (char*)evt->data);
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_DISCONNECTED");
            break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGI("HTTPClient", "HTTP_EVENT_REDIRECT");
            break;
    }
    return ESP_OK;
}

HTTPApiClient::HTTPApiClient()
{
}

void HTTPApiClient::HTTPClient_init()
{
    httpClientConfig  =  {0};
    httpClientConfig.url = API_URI;
    httpClientConfig.cert_pem = PEM_CERT;
    httpClientConfig.event_handler = _http_event_handle; 

    client = esp_http_client_init(&httpClientConfig);   
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK)
    {
        std::cout<< "Status , content_length" <<
                 esp_http_client_get_status_code(client)<<"  "<<
                 esp_http_client_get_content_length(client)<<std::endl;
    }
    esp_http_client_cleanup(client);
}

void HTTPApiClient::PostPacketToApi(std::string json, const char *  URL)
{
    // std::cout<<json <<"     "<<URL;
    httpClientConfig = {0};
    httpClientConfig.url = URL;
    httpClientConfig.event_handler = _http_event_handle;
    httpClientConfig.cert_pem = PEM_CERT;
    httpClientConfig.method = HTTP_METHOD_POST;

    client = esp_http_client_init(&httpClientConfig);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, json.c_str(), json.size());
    esp_http_client_set_header(client, "Content-Type", "application/json");
    // httpClientConfig = {0};
    // httpClientConfig.url = URL;
    // httpClientConfig.event_handler = _http_event_handle;
    // esp_http_client_set_post_field(client, json.data(),json.size());
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        std::cout<<"##### HTTP POST Status = "<<esp_http_client_get_status_code(client)<<std::endl;
    } else {
        ESP_LOGW("TAG", "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
}
void HTTPApiClient::GetHttpRequestsTask(void)
{

}
