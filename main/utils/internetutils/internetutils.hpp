#ifndef _INTERNETUTILS
#define _INTERNETUTILS
#include "utils/util.hpp"

class InternetUtils
{
    public:
        static bool check_internet_connection_status();
        static std::string getMacId();
};

#endif 