#ifndef _UTILS
#define _UTILS

// Logging Includes
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"

// Wifi STA Mode
#include "esp_wifi.h"

// SoftAp specific includes
#include "esp_mac.h"
#include "esp_wifi.h"
#include "lwip/err.h"
#include "lwip/sys.h"

//RTOS includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

// HTTP Server include 
#include "esp_http_server.h"

// GPIO library
#include "driver/i2c.h"

// NVS memory
#include "nvs.h"
#include "nvs_flash.h"

// standard
#include <iostream>
#include <string>
#include <vector>
#include <string.h>

#endif //_UTILS