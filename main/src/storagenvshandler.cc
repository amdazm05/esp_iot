#include "storagenvshandler.hpp"

StorageHandler * StorageHandler::_inst = nullptr;
nvs_handle StorageHandler::handle;

StorageHandler::StorageHandler()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    {
        const esp_partition_t* nvs_partition = 
        esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
        ESP_ERROR_CHECK( esp_partition_erase_range(nvs_partition, 0, nvs_partition->size) );
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
        ESP_LOGE("NVS","No free pages erasing");
    }
    ESP_ERROR_CHECK(ret);

    ret = nvs_open("storage", NVS_READWRITE, &handle);
    ESP_ERROR_CHECK(ret);
    nvs_close(handle);

}

void StorageHandler::erase_nvs()
{
    nvs_flash_erase();
}

void StorageHandler::init()
{
    _inst = new StorageHandler;
}

StorageHandler * StorageHandler::get_instance()
{
    return _inst;
}
void StorageHandler::write_to_nvs(std::string & key,std::string & value)
{
    nvs_open("storage", NVS_READWRITE, &handle);
    if(key.size() && value.size())
    {
        esp_err_t ret = nvs_set_str(handle, key.c_str(), value.c_str());
        
        if (ret == ESP_OK)
        {
            ESP_LOGI("NVS","Stored value string into NVS: %s\n", value.c_str());
            ret = nvs_commit(handle);
        }
        else
        {
            ESP_LOGE("NVS","Could not store value string into NVS");
        }
    }
    nvs_close(handle);
}

std::size_t StorageHandler::read_from_nvs(std::string& key,std::string& value)
{
    // both strings must be reserved before calling the sequence
    std::size_t bytesReturned =-1;
    nvs_open("storage", NVS_READWRITE, &handle);
    ESP_LOGI("NVS"," Key searched : %s", key.c_str());
    char *value_ = nullptr;
    if (nvs_get_str(handle,  key.c_str(), nullptr, &bytesReturned) == ESP_OK)
    {
        if ( bytesReturned > 0)
        {
            value_ = (char *)malloc(bytesReturned);
            if(nvs_get_str(handle, key.c_str(), value_, &bytesReturned)==ESP_OK)
            {
                // value=value_;
                std::string copyval(value_);
                value = copyval;
                ESP_LOGI("NVS","string value retrieved: %s\n", value_);
            }
        }
    }

    else
    {
        ESP_LOGE("NVS","Could not retrieve stored value string from NVS");
        // do nothing 
    }
    
    nvs_close(handle);
    return bytesReturned;
}

