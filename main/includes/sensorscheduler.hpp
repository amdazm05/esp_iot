#ifndef _SENSOR_SCHEDULER
#define _SENSOR_SCHEDULER

#include "util.hpp"
#include "env/env.hpp"
#include "bme680.h"

class SensorScheduler
{
    public:
        SensorScheduler();
        ~SensorScheduler();
        static void bme_680_polling_task(void *pvParameters);
    private:
        static bme680_sensor_t *bme_sensor_obj;

};

#endif //_SENSOR_SCHEDULER
