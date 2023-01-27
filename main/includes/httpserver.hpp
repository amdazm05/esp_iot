#ifndef _HTTP_SERVER
#define _HTTP_SERVER
// UTILS
#include "util.hpp"

// URI handlers 
#include "httpurihandlers.hpp"

// Class specific import 
#include "esp_http_server.h"

class Http_Server
{
    public:
        Http_Server(int serverport);
        static void startHttpServer(void);
        static void stopHttpServer(void);
    private:
        static int serverport;
        static httpd_config_t httpServerConfiguration ;
        static httpd_handle_t httpServerInstance ;
        
        static httpd_uri_t testUri ;
        static httpd_uri_t SSIDuri ;
        static httpd_uri_t PWDuri;

};

#endif //_HTTP_SERVER