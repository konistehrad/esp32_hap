#pragma once
#include "include/homekit_services.h"
#include "include/homekit_characteristics.h"
#include "hk_session.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    size_t id;
    hk_characteristics_t type;
    void *static_value;
    void *(*read)();
    void (*write)(void *);
    bool can_notify;
    hk_session_t *session;
} hk_characteristic_t;

typedef struct
{
    size_t id;
    hk_services_t type;
    bool primary;
    bool hidden;
    hk_characteristic_t *characteristics;
} hk_service_t;

typedef struct
{
    size_t id;
    hk_service_t *services;
} hk_accessory_t;

typedef enum
{
    HK_FORMAT_BOOL,
    HK_FORMAT_UINT8,
    HK_FORMAT_UINT16,
    HK_FORMAT_UINT32,
    HK_FORMAT_UINT64,
    HK_FORMAT_INT,
    HK_FORMAT_FLOAT,
    HK_FORMAT_STRING,
    HK_FORMAT_TLV8,
    HK_FORMAT_DATA,
    HK_FORMAT_UNKNOWN
} hk_format_t;

void hk_accessories_store_add_accessory();
void hk_accessories_store_add_service(hk_services_t service_type, bool primary, bool hidden);
void hk_accessories_store_add_characteristic(hk_characteristics_t characteristic_type, void *(*read)(), void (*write)(void *), bool can_notify);
void hk_accessories_store_add_characteristic_static_read(hk_characteristics_t type, void *value);
void hk_accessories_store_end_config();

hk_format_t hk_accessories_store_get_format(hk_characteristics_t characteristic_type);

hk_accessory_t *hk_accessories_store_get_accessories();
hk_characteristic_t *hk_accessories_store_get_characteristic(size_t aid, size_t iid);
hk_characteristic_t *hk_accessories_store_get_identify_characteristic();