#include "internetutils.hpp"

bool InternetUtils::check_internet_connection_status() 
{
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int err = getaddrinfo("www.google.com", "80", &hints, &res);

    if(err != ESP_OK) {
        return false;
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        freeaddrinfo(res);
        return false;
    }

    err = connect(sock, res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);
    close(sock);

    if (err != ESP_OK) {
        return false;
    }

    return true;
}

std::string InternetUtils::getMacId()
{
    uint8_t mac[6];
    esp_efuse_mac_get_default(mac);
    std::stringstream macaddress;

    macaddress << std::hex 
            << (uint16_t)mac[0] 
    << ":" << (uint16_t)mac[1] 
    << ":" << (uint16_t)mac[2] 
    << ":" << (uint16_t)mac[3] 
    << ":" << (uint16_t)mac[4] 
    << ":" << (uint16_t)mac[5];

    return std::move(macaddress.str());
}