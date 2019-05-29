#include "include/homekit.h"
#include "utils/hk_logging.h"
#include "utils/hk_store.h"
#include "hk_server.h"
#include "hk_mdns.h"
#include "hk_accessories_store.h"
#include "hk_pairings_store.h"

void hk_init(const char *name, hk_categories_t category, const char *code, esp_log_level_t log_level)
{
    esp_log_level_set("homekit", log_level);

    hk_store_init();
    hk_mdns_init(name, category, 2);
    hk_server_start();

    hk_store_code_set(code);
    ESP_LOGI("homekit", "Inititialized.");
    hk_pairings_log_devices();
}

void hk_setup_start()
{
}

void hk_setup_add_accessory(const char *name, const char *manufacturer, const char *model, const char *serial_number, const char *revision, void (*identify)())
{
    hk_accessories_store_add_accessory();
    hk_accessories_store_add_service(HK_SRV_ACCESSORY_INFORMATION, false, false);

    hk_accessories_store_add_characteristic_static_read(HK_CHR_NAME, (void *)name);
    hk_accessories_store_add_characteristic_static_read(HK_CHR_MANUFACTURER, (void *)manufacturer);
    hk_accessories_store_add_characteristic_static_read(HK_CHR_MODEL, (void *)model);
    hk_accessories_store_add_characteristic_static_read(HK_CHR_SERIAL_NUMBER, (void *)serial_number);
    hk_accessories_store_add_characteristic_static_read(HK_CHR_FIRMWARE_REVISION, (void *)revision);
    hk_accessories_store_add_characteristic(HK_CHR_IDENTIFY, NULL, identify, false);
}

void hk_setup_add_service(hk_services_t service_type, bool primary, bool hidden)
{
    hk_accessories_store_add_service(service_type, primary, hidden);
}

void hk_setup_add_characteristic(hk_characteristics_t type, void *(*read)(), void (*write)(void *), bool can_notify)
{
    hk_accessories_store_add_characteristic(type, read, write, can_notify);
}

void hk_setup_finish()
{
    hk_accessories_store_end_config();
    ESP_LOGI("homekit", "Set up.");
}

void hk_reset()
{
    HK_LOGD("Resetting homekit for this device.");
    hk_pairings_store_remove_all();
    hk_store_is_paired_set(false);
    hk_mdns_update_paired(false);
}