#include "httpserver.hpp"

#define HTTP_METHOD HTTP_POST
#define URI_STRING "/test"


int Http_Server::serverport;
httpd_config_t Http_Server::httpServerConfiguration ;
httpd_handle_t Http_Server::httpServerInstance ;
httpd_uri_t Http_Server::testUri;

// URI settings in constructor
Http_Server::Http_Server(int server_port)
{
    serverport = server_port ;

    // URI settings
    testUri.uri       = URI_STRING;
    testUri.method    = HTTP_GET;
    testUri.handler   = methodHandler;
    testUri.user_ctx  = NULL;
}
void Http_Server::startHttpServer(void)
{
    Http_Server::httpServerConfiguration = HTTPD_DEFAULT_CONFIG();
    Http_Server::httpServerConfiguration.server_port = Http_Server::serverport;
    if(httpd_start(&Http_Server::httpServerInstance, &Http_Server::httpServerConfiguration) == ESP_OK)
    {
        ESP_ERROR_CHECK(httpd_register_uri_handler(Http_Server::httpServerInstance, &Http_Server::testUri));
    }   
}
void Http_Server::stopHttpServer(void)
{
    if(httpServerInstance != NULL)
    {
        ESP_ERROR_CHECK(httpd_stop(Http_Server::httpServerInstance));
    }
}