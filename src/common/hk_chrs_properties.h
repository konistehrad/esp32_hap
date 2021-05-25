/**
 * @file hk_chrs_properties.h
 *
 * Functions to work with homekit properties.
 */

#pragma once

#include <freertos/FreeRTOS.h>

#include "../include/hk_chrs.h"
#include "../include/hk_mem.h"

typedef enum
{
    HK_FORMAT_BOOL,
    HK_FORMAT_UINT8,
    HK_FORMAT_UINT16,
    HK_FORMAT_UINT32,
    HK_FORMAT_UINT64,
    HK_FORMAT_INT,
    HK_FORMAT_FLOAT,
    HK_FORMAT_FLOAT_CELSIUS,
    HK_FORMAT_STRING,
    HK_FORMAT_TLV8,
    HK_FORMAT_DATA,
    HK_FORMAT_UNKNOWN
} hk_format_t;


typedef enum
{
    HK_CHR_PROP_SUPPORTS_READ = 0x0001,
    HK_CHR_PROP_SUPPORTS_WRITE = 0x0002,
    HK_CHR_PROP_SUPPORTS_ADDITIONAL_AUTH_DATA = 0x0004,
    HK_CHR_PROP_REQUIRES_TIMED_WRITE = 0x0008,
    HK_CHR_PROP_SUPPORTS_SECURE_READS = 0x0010,
    HK_CHR_PROP_SUPPORTS_SECURE_WRITES = 0x0020,
    HK_CHR_PROP_HIDDEN_FROM_USER = 0x0040,
    HK_CHR_PROP_NOTIFIES_EVENTS_CONNECTED_STATE = 0x0080,
    HK_CHR_PROP_NOTIFIES_EVENTS_DISCONNECTED_STATE = 0x0100,
    HK_CHR_PROP_SUPPORTS_BROADCAST_NOTIFY = 0x0200
} hk_chr_prop_t;

// 7.3.3.4 HAP PDU Body
typedef enum
{
    HK_DESC_NONE = 0,
    HK_DESC_VALID_RANGE = 0x0D,
    HK_DESC_STEP_VALUE = 0x0E,
    HK_DESC_VALID_VALUES = 0x11,
    HK_DESC_VALID_VALUES_RANGE = 0x12,
} hk_desc_type_t;

typedef struct
{
    hk_desc_type_t type;
    hk_mem data;
} hk_desc_t;

/**
 * @brief Returns the format of a characteristic type
 *
 * Returns the format of a characteristic type.
 *
 * @param chr_type The type of the characteristic.
 * 
 * @return Retruns the format.
 */
 hk_format_t hk_chrs_properties_get_type(hk_chr_types_t chr_type);

/**
 * @brief Returns the properties of a characteristic type
 *
 * Returns the properties (can be written, can be read, notifies, ...) of a characteristic type.
 *
 * @param chr_type The type of the characteristic.
 * 
 * @return Retruns a bitfield with the properties.
 */
 uint16_t hk_chrs_properties_get_prop(hk_chr_types_t chr_type);

 /**
 * @brief Returns the descriptors for a characteristic type.
 *
 * @param chr_type The type of the characteristic.
 * 
 * @return Returns the descriptor array terminated with a `result_len` set to number of descriptors.
 */
 hk_desc_t *hk_chrs_properties_descriptors(hk_chr_types_t chr_type, size_t *result_len);