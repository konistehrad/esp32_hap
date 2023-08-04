#include "hk_chr_timed_write.h"

#include <time.h>

#include "../../../utils/hk_logging.h"
#include "../../../utils/hk_tlv.h"

#include "../hk_formats_ble.h"

hk_mem *hk_chr_timed_write_write_request;
time_t time_of_death = -1;

esp_err_t hk_chr_timed_write(hk_transaction_t *transaction, hk_chr_t *chr)
{
    esp_err_t ret = ESP_OK;
    uint8_t ttl = 0;
    hk_mem *ttl_mem = hk_mem_init();
    hk_tlv_t *tlv_data_request = hk_tlv_deserialize(transaction->request);
    hk_chr_timed_write_write_request = hk_mem_init();

    if (hk_tlv_get_mem_by_type(tlv_data_request, 0x01, hk_chr_timed_write_write_request) != ESP_OK)
    {
        HK_LOGE("Error getting value of write request.");
        ret = ESP_ERR_INVALID_ARG;
    }

    if (ret == ESP_OK)
    {
        if (hk_tlv_get_mem_by_type(tlv_data_request, 0x08, ttl_mem) != ESP_OK)
        {
            HK_LOGE("Error getting value of write request.");
            ret = ESP_ERR_INVALID_ARG;
        }
    }

    if (ret == ESP_OK)
    {
        ttl = *(uint8_t *)ttl_mem->ptr;
        time_t now;
        time(&now);
        time_of_death = now + ttl;
        HK_LOGD("Timed write requested. Now: %lld, Time to live: %d, Time of death: %lld", now, ttl, time_of_death);
    }

    hk_mem_free(ttl_mem);
    hk_tlv_free(tlv_data_request);
    return ret;
}

esp_err_t hk_chr_execute_write(hk_connection_t *connection, hk_transaction_t *transaction, hk_chr_t *chr)
{
    esp_err_t ret = ESP_OK;
    hk_mem *write_response = hk_mem_init();
    time_t now;
    time(&now);

    if (now > time_of_death)
    {
        HK_LOGD("Time of death: %lld, Now: %lld", time_of_death, now);
        HK_LOGE("Execute of timed write could not be done, as time was over.");
        ret = ESP_ERR_NOT_SUPPORTED;
    }
    else
    {
        HK_LOGD("Executing timed write: Time of death: %lld, Now: %lld", time_of_death, now);
    }

    if (ret == ESP_OK)
    {
        if (chr->write_callback != NULL)
        {
            ret = chr->write_callback(hk_chr_timed_write_write_request);
        }
        else if (chr->write_with_response_callback)
        {
            ret = chr->write_with_response_callback(connection, hk_chr_timed_write_write_request, write_response);
        }
        else
        {
            HK_LOGE("Write callback was not found.");
            ret = ESP_ERR_NOT_FOUND;
        }
    }

    if (ret == ESP_OK)
    {
        if (write_response->size > 0)
        {
            hk_tlv_t *tlv_data_response = NULL;
            tlv_data_response = hk_tlv_add_mem(tlv_data_response, 0x01, write_response);
            hk_tlv_serialize(tlv_data_response, transaction->response);
        }
    }

    hk_mem_free(write_response);
    hk_mem_free(hk_chr_timed_write_write_request);
    return ret;
}