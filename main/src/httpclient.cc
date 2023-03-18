#include "httpclient.hpp"

esp_http_client_config_t HTTPApiClient::httpClientConfigGet = {0};
esp_http_client_config_t HTTPApiClient::httpClientConfigPost = {0};


esp_http_client_handle_t HTTPApiClient::clientWrite={0};
esp_http_client_handle_t HTTPApiClient::client={0};
int HTTPApiClient::recievedBytes=0;

char HTTPApiClient::buffer[1<<10];

esp_err_t HTTPApiClient::_http_event_handle_write(esp_http_client_event_t *evt)
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
            ESP_LOGI("HTTPClient", "HTTP_EVENT_ON_DATA, len=%d \n ", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) 
            {
                printf("\n %.*s \n", evt->data_len, (char*)evt->data);
            }
            recievedBytes+=evt->data_len;
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


esp_err_t HTTPApiClient::_http_event_handle(esp_http_client_event_t *evt)
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
            ESP_LOGI("HTTPClient", "HTTP_EVENT_ON_DATA, len=%d \n ", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) 
            {
                printf("\n %.*s \n", evt->data_len, (char*)evt->data);
                std::copy((char*)evt->data, (char*)evt->data+ evt->data_len , buffer+recievedBytes);
            }
            recievedBytes+=evt->data_len;
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

std::string HTTPApiClient::GetPacketFromAPI(const char *  URL)
{
    memset(buffer,0,sizeof(buffer));
    recievedBytes =0;
    httpClientConfigGet  =  {0};
    httpClientConfigGet.url = URL;
    httpClientConfigGet.cert_pem = PEM_CERT;
    httpClientConfigGet.event_handler = HTTPApiClient::_http_event_handle; 

    client = esp_http_client_init(&httpClientConfigGet);   
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK)
    {
        std::cout<< "Read content_length :" <<esp_http_client_get_content_length(client)<<std::endl;
    }
    esp_http_client_cleanup(client);
    return std::move(std::string(buffer));

}

void HTTPApiClient::PostPacketToApi(std::string && json, const char *  URL)
{
    ESP_LOGW("WARN","%s",URL );
    httpClientConfigPost = {0};
    httpClientConfigPost.url = URL;
    httpClientConfigPost.event_handler = _http_event_handle_write;
    httpClientConfigPost.cert_pem = PEM_CERT;
    httpClientConfigPost.method = HTTP_METHOD_POST;

    clientWrite = esp_http_client_init(&httpClientConfigPost);
    esp_http_client_set_method(clientWrite, HTTP_METHOD_POST);
    esp_http_client_set_post_field(clientWrite, json.c_str(), json.size());
    esp_http_client_set_header(clientWrite, "Content-Type", "application/json");

    esp_err_t err = esp_http_client_perform(clientWrite);
    if (err == ESP_OK) {
        std::cout<<"HTTP POST Status : "<<esp_http_client_get_status_code(clientWrite)<<std::endl;
    } else {
        ESP_LOGW("HTTPClient", "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(clientWrite);
}
