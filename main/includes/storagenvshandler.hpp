#ifndef _STORAGE_HANDLER
#define _STORAGE_HANDLER

#include "util.hpp"

class StorageHandler
{
    public:
        static void init();
        static void erase_nvs();
        static StorageHandler * get_instance();
        static void write_to_nvs(std::string & key,std::string & value);
        static std::size_t read_from_nvs(std::string& key,std::string& value);
    private:
        static nvs_handle handle;
        StorageHandler();
        static StorageHandler * _inst;
};

#endif //_STORAGE_HANDLER