#include "hk_pair_verify.h"

#include "../utils/hk_logging.h"
#include "../utils/hk_tlv.h"
#include "../utils/hk_util.h"
#include "../utils/hk_store.h"
#include "hk_pairings_store.h"
#include "hk_pair_tlvs.h"

static esp_err_t hk_pairings_add(hk_mem *conn_device_id, hk_tlv_t *request_tlvs, hk_tlv_t **response_tlvs_ptr, bool *is_paired)
{
    HK_LOGI("Add pairing.");

    *is_paired = true;
    bool is_admin = false;
    hk_tlv_t *response_tlvs = NULL;
    hk_mem *device_id = hk_mem_init();
    hk_mem *device_long_term_key_public = hk_mem_init();
    esp_err_t ret = ESP_OK;

    RUN_AND_CHECK(ret, hk_tlv_get_mem_by_type, request_tlvs, HK_PAIR_TLV_IDENTIFIER, device_id);
    RUN_AND_CHECK(ret, hk_pairings_store_is_admin, conn_device_id, &is_admin);
    RUN_AND_CHECK(ret, hk_tlv_get_mem_by_type, request_tlvs, HK_PAIR_TLV_PUBLICKEY, device_long_term_key_public);

    if (is_admin)
    {
        bool exists = false;
        if (hk_pairings_store_device_exists(device_id, &exists) == ESP_OK && exists) {
            HK_LOGE("Updating existing pairing is not implemented at the moment.");
        } else {
            RUN_AND_CHECK(ret, hk_pairings_store_add, device_id, device_long_term_key_public, true);
            HK_LOGI("Adding a new pairing %d", ret);
        }
    }
    else
    {
        response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_ERROR, HK_PAIR_TLV_ERROR_AUTHENTICATION);
    }

    if (ret != ESP_OK)
    {
        response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_ERROR, HK_PAIR_TLV_ERROR_UNKNOWN);
    }

    response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_STATE, HK_PAIR_TLV_STATE_M2); //state M2 is always returned

    *response_tlvs_ptr = response_tlvs;
    hk_mem_free(device_id);

    return ret;
}

static esp_err_t hk_pairings_remove(hk_tlv_t *request_tlvs, hk_tlv_t **response_tlvs_ptr, bool *is_paired)
{
    HK_LOGI("Remove pairing.");

    *is_paired = true;
    bool is_admin = false;
    bool has_admin_pairing = false;
    hk_tlv_t *response_tlvs = NULL;
    hk_mem *device_id = hk_mem_init();
    esp_err_t ret = ESP_OK;

    RUN_AND_CHECK(ret, hk_tlv_get_mem_by_type, request_tlvs, HK_PAIR_TLV_IDENTIFIER, device_id);
    RUN_AND_CHECK(ret, hk_pairings_store_is_admin, device_id, &is_admin);

    if (is_admin)
    {
        RUN_AND_CHECK(ret, hk_pairings_store_remove, device_id);
        RUN_AND_CHECK(ret, hk_pairings_store_has_admin_pairing, &has_admin_pairing);
        if (!has_admin_pairing)
        {
            HK_LOGD("Removing all pairings, because no further admin pairing.");
            RUN_AND_CHECK(ret, hk_pairings_store_remove_all);
            *is_paired = false;
        }
    }
    else
    {
        response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_ERROR, HK_PAIR_TLV_ERROR_AUTHENTICATION);
    }

    if (ret != ESP_OK)
    {
        response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_ERROR, HK_PAIR_TLV_ERROR_UNKNOWN);
    }

    response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_STATE, HK_PAIR_TLV_STATE_M2); //state M2 is always returned

    *response_tlvs_ptr = response_tlvs;
    hk_mem_free(device_id);

    return ret;
}

static esp_err_t hk_pairings_list(hk_mem *conn_device_id, hk_tlv_t *request_tlvs, hk_tlv_t **response_tlvs_ptr)
{
    HK_LOGI("List pairing.");

    bool is_admin = false;
    hk_tlv_t *response_tlvs = NULL;
    hk_mem *device_id = hk_mem_init();
    hk_mem *device_long_term_key_public = hk_mem_init();
    esp_err_t ret = ESP_OK;

    RUN_AND_CHECK(ret, hk_tlv_get_mem_by_type, request_tlvs, HK_PAIR_TLV_IDENTIFIER, device_id);
    RUN_AND_CHECK(ret, hk_pairings_store_is_admin, conn_device_id, &is_admin);

    if (is_admin)
    {
        HK_LOGE("Updating existing pairing is not implemented at the moment.");
        ret = ESP_ERR_NOT_SUPPORTED;
    }
    else
    {
        response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_ERROR, HK_PAIR_TLV_ERROR_AUTHENTICATION);
    }

    if (ret != ESP_OK)
    {
        response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_ERROR, HK_PAIR_TLV_ERROR_UNKNOWN);
    }

    response_tlvs = hk_tlv_add_uint8(response_tlvs, HK_PAIR_TLV_STATE, HK_PAIR_TLV_STATE_M2); //state M2 is always returned

    *response_tlvs_ptr = response_tlvs;
    hk_mem_free(device_id);

    return ret;
}

esp_err_t hk_pairings(hk_mem *conn_device_id, hk_mem *request, hk_mem *response, bool *kill_session, bool *is_paired)
{
    HK_LOGD("Pairings");
    esp_err_t ret = ESP_OK;
    hk_tlv_t *tlv_data_request = hk_tlv_deserialize(request);
    hk_tlv_t *tlv_data_response = NULL;
    hk_tlv_t *type_tlv = hk_tlv_get_tlv_by_type(tlv_data_request, HK_PAIR_TLV_STATE);

    if (type_tlv == NULL)
    {
        HK_LOGE("Could not find tlv with type state.");
        ret = ESP_ERR_INVALID_ARG;
    }

    if (ret == ESP_OK)
    {
        if (*type_tlv->value != 1)
        {
            HK_LOGE("Unexpected state.");
            ret = ESP_ERR_INVALID_ARG;
        }
    }

    hk_tlv_t *method_tlv = NULL;
    if (ret == ESP_OK)
    {
        method_tlv = hk_tlv_get_tlv_by_type(tlv_data_request, HK_PAIR_TLV_METHOD);
        if (method_tlv == NULL)
        {
            HK_LOGE("Could not find tlv with type method.");
            ret = ESP_ERR_INVALID_ARG;
        }
    }

    if (ret == ESP_OK)
    {
        switch (*method_tlv->value)
        {
        case 3:
            RUN_AND_CHECK(ret, hk_pairings_add, conn_device_id, tlv_data_request, &tlv_data_response, is_paired);
            break;
        case 4:
            RUN_AND_CHECK(ret, hk_pairings_remove, tlv_data_request, &tlv_data_response, is_paired);

            if (ret == ESP_OK)
            {
                *kill_session = true; // We kill all sessions, anyway if device was removed. This is for simplicity. Homekit reconnects in this case.
            }
            break;
        case 5:
            RUN_AND_CHECK(ret, hk_pairings_list, conn_device_id, tlv_data_response, &tlv_data_response);
            break;
        default:
            HK_LOGE("Unexpected value in tlv in pairing: %d", *type_tlv->value);
            ret = ESP_ERR_INVALID_ARG;
        }
    }

    hk_tlv_serialize(tlv_data_response, response);

    hk_tlv_free(tlv_data_request);
    hk_tlv_free(tlv_data_response);

    return ret;
}