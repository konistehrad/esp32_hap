#include "hk_accessory_id.h"

#include <esp_system.h>
#include <esp_random.h>

#include "../utils/hk_store.h"
#include "../utils/hk_util.h"

#define HK_ACCESSORY_ID_STORE_KEY "hk_accessory_id"

esp_err_t hk_accessory_id_get(hk_mem *id)
{
    esp_err_t ret = hk_store_blob_get(HK_ACCESSORY_ID_STORE_KEY, id);

    if (ret == ESP_ERR_NOT_FOUND || id->size < 1)
    {
        hk_mem_set(id, 0);
        //create new 6 byte accessory id
        uint32_t random_number = esp_random();
        hk_mem_append_buffer(id, &random_number, sizeof(uint32_t));
        random_number = esp_random();
        hk_mem_append_buffer(id, &random_number, sizeof(uint16_t));

        ret = hk_store_blob_set(HK_ACCESSORY_ID_STORE_KEY, id);

        char id_str[18];
        sprintf(id_str, "%02X:%02X:%02X:%02X:%02X:%02X",
                id->ptr[0], id->ptr[1], id->ptr[2],
                id->ptr[3], id->ptr[4], id->ptr[5]);
        HK_LOGD("Created new accessory id: %s", id_str);
    }

    return ret;
}

esp_err_t hk_accessory_id_get_serialized(hk_mem *id)
{
    hk_mem *id_mem = hk_mem_init();
    hk_mem_set(id_mem, 6);

    esp_err_t ret = hk_accessory_id_get(id_mem);
    if (ret == ESP_OK)
    {
        hk_mem_set(id, 18);
        sprintf(id->ptr, "%02X:%02X:%02X:%02X:%02X:%02X",
                id_mem->ptr[0], id_mem->ptr[1], id_mem->ptr[2],
                id_mem->ptr[3], id_mem->ptr[4], id_mem->ptr[5]);
        hk_mem_set(id, 17); // trim newline
    }

    hk_mem_free(id_mem);
    return ret;
}

esp_err_t hk_accessory_id_reset()
{
    HK_LOGD("Deleting accessory id.");
    esp_err_t ret = ESP_OK;
    ret = hk_store_erase(HK_ACCESSORY_ID_STORE_KEY);

    if (ret == ESP_ERR_NVS_NOT_FOUND)
    {
        ret = ESP_OK;
    }
    else if(ret != ESP_OK)
    {
        HK_LOGE("Error resetting accessory id: %s (%d)", esp_err_to_name(ret), ret);
    }

    return ret;
}