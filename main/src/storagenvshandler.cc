#include "storagenvshandler.hpp"

StorageHandler * StorageHandler::_inst = nullptr;

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
    }
    ESP_ERROR_CHECK(ret);

    ret = nvs_open("storage", NVS_READWRITE, &handle);
    ESP_ERROR_CHECK(ret);
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

}

std::size_t StorageHandler::read_from_nvs(std::string & value)
{
    std::size_t bytesReturned;

    esp_err_t err = nvs_get_str(handle, "my_string_key", (char *)value.data(),&bytesReturned);
    if (err == ESP_OK)
    {
        printf("string value: %s\n", value.c_str());
    }
    return bytesReturned;
}

