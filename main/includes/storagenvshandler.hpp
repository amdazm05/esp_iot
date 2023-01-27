#ifndef _STORAGE_HANDLER
#define _STORAGE_HANDLER

#include "util.hpp"

class StorageHandler
{
    public:
        static void init();
        static StorageHandler * get_instance();
        void write_to_nvs(std::string & key,std::string & value);
        std::size_t read_from_nvs(std::string & value);
    private:
        nvs_handle handle;
        StorageHandler();
        static StorageHandler * _inst;
};

#endif //_STORAGE_HANDLER