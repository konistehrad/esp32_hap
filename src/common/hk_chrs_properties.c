#include "hk_chrs_properties.h"

#include "../utils/hk_logging.h"

hk_format_t hk_chrs_properties_get_type(hk_chr_types_t chr_type)
{
    switch (chr_type)
    {
    case HK_CHR_ADMINISTRATOR_ONLY_ACCESS:
    case HK_CHR_AUDIO_FEEDBACK:
    case HK_CHR_IDENTIFY:
    case HK_CHR_MOTION_DETECTED:
    case HK_CHR_OBSTRUCTION_DETECTED:
    case HK_CHR_ON:
    case HK_CHR_OUTLET_IN_USE:
    case HK_CHR_HOLD_POSITION:
    case HK_CHR_STATUS_ACTIVE:
    case HK_CHR_MUTE:
    case HK_CHR_NIGHT_VISION:
    case HK_CHR_ACTIVE:
    case HK_CHR_SWING_MODE:
    case HK_CHR_LOCK_PHYSICAL_CONTROLS:
        return HK_FORMAT_BOOL;
    case HK_CHR_CURRENT_DOOR_STATE:
    case HK_CHR_CURRENT_HEATING_COOLING_STATE:
    case HK_CHR_LOCK_CURRENT_STATE:
    case HK_CHR_LOCK_LAST_KNOWN_ACTION:
    case HK_CHR_LOCK_MANAGEMENT_AUTO_SECURITY_TIMEOUT:
    case HK_CHR_LOCK_TARGET_STATE:
    case HK_CHR_TARGET_DOORSTATE:
    case HK_CHR_TARGET_HEATING_COOLING_STATE:
    case HK_CHR_TEMPERATURE_DISPLAY_UNITS:
    case HK_CHR_AIR_PARTICULATE_SIZE:
    case HK_CHR_SECURITY_SYSTEM_CURRENT_STATE:
    case HK_CHR_SECURITY_SYSTEM_TARGET_STATE:
    case HK_CHR_BATTERY_LEVEL:
    case HK_CHR_CARBON_MONOXIDE_DETECTED:
    case HK_CHR_CONTACT_SENSOR_STATE:
    case HK_CHR_CURRENT_POSITION:
    case HK_CHR_LEAK_DETECTED:
    case HK_CHR_OCCUPANCY_DETECTED:
    case HK_CHR_POSITION_STATE:
    case HK_CHR_PROGRAMMABLE_SWITCH_EVENT:
    case HK_CHR_SMOKE_DETECTED:
    case HK_CHR_STATUS_FAULT:
    case HK_CHR_STATUS_JAMMED:
    case HK_CHR_STATUS_LOW_BATTERY:
    case HK_CHR_STATUS_TAMPERED:
    case HK_CHR_TARGET_POSITION:
    case HK_CHR_SECURITY_SYSTEM_ALARM_TYPE:
    case HK_CHR_CHARGING_STATE:
    case HK_CHR_CARBON_DIOXIDE_DETECTED:
    case HK_CHR_AIR_QUALITY:
    case HK_CHR_VOLUME:
    case HK_CHR_CURRENT_AIR_PURIFIER_STATE:
    case HK_CHR_CURRENT_SLAT_STATE:
    case HK_CHR_SLAT_TYPE:
    case HK_CHR_FILTER_CHANGE_INDICATION:
    case HK_CHR_RESET_FILTER_INDICATION:
    case HK_CHR_TARGET_AIR_PURIFIER_STATE:
    case HK_CHR_TARGET_FAN_STATE:
    case HK_CHR_CURRENT_FAN_STATE:
    case HK_CHR_SERVICE_LABEL_INDEX:
    case HK_CHR_SERVICE_LABEL_NAMESPACE:
    case HK_CHR_PAIRING_FEATURES:
    case HK_CHR_CURRENT_HEATER_COOLER_STATE:
    case HK_CHR_TARGET_HEATER_COOLER_STATE:
        return HK_FORMAT_UINT8;
    case HK_CHR_ACCESSORY_FLAGS:
    case HK_CHR_COLOR_TEMPERATURE:
        return HK_FORMAT_UINT32;
    // case HK_CHR:
    //     return HK_FORMAT_UINT64
    case HK_CHR_BRIGHTNESS:
    case HK_CHR_ROTATION_DIRECTION:
    case HK_CHR_CURRENT_HORIZONTAL_TILT_ANGLE:
    case HK_CHR_CURRENT_VERTICAL_TILT_ANGLE:
    case HK_CHR_TARGET_HORIZONTAL_TILT_ANGLE:
    case HK_CHR_TARGET_VERTICAL_TILT_ANGLE:
    case HK_CHR_CURRENT_TILT_ANGLE:
    case HK_CHR_TARGET_TILT_ANGLE:
        return HK_FORMAT_INT;
    case HK_CHR_CURRENT_RELATIVE_HUMIDITY:
    case HK_CHR_HUE:
    case HK_CHR_ROTATION_SPEED:
    case HK_CHR_SATURATION:
    case HK_CHR_AIR_PARTICULATE_DENSITY:
    case HK_CHR_CURRENT_AMBIENT_LIGHT_LEVEL:
    case HK_CHR_CARBON_MONOXIDE_LEVEL:
    case HK_CHR_CARBON_MONOXIDE_PEAK_LEVEL:
    case HK_CHR_CARBON_DIOXIDE_LEVEL:
    case HK_CHR_CARBON_DIOXIDE_PEAK_LEVEL:
    case HK_CHR_OPTICAL_ZOOM:
    case HK_CHR_DIGITAL_ZOOM:
    case HK_CHR_IMAGE_ROTATION:
    case HK_CHR_IMAGE_MIRRORING:
    case HK_CHR_FILTER_LIFE_LEVEL:
    case HK_CHR_OZONE_DENSITY:
    case HK_CHR_NITROGEN_DIOXIDE_DENSITY:
    case HK_CHR_SULPHUR_DIOXIDE_DENSITY:
    case HK_CHR_PM25_DENSITY:
    case HK_CHR_PM10_DENSITY:
    case HK_CHR_VOC_DENSITY:
    case HK_CHR_TARGET_RELATIVE_HUMIDITY:
        return HK_FORMAT_FLOAT;
    case HK_CHR_COOLING_THRESHOLD_TEMPERATURE:
    case HK_CHR_HEATING_THRESHOLD_TEMPERATURE:
    case HK_CHR_CURRENT_TEMPERATURE:
    case HK_CHR_TARGET_TEMPERATURE:
        return HK_FORMAT_FLOAT_CELSIUS;
    case HK_CHR_FIRMWARE_REVISION:
    case HK_CHR_HARDWARE_REVISION:
    case HK_CHR_MANUFACTURER:
    case HK_CHR_MODEL:
    case HK_CHR_NAME:
    case HK_CHR_SERIAL_NUMBER:
    case HK_CHR_VERSION:
        return HK_FORMAT_STRING;
    case HK_CHR_LOCK_CONTROL_POINT:
    case HK_CHR_LOGS:
    case HK_CHR_STREAMING_STATUS:
    case HK_CHR_SUPPORTED_VIDEO_STREAMING_CONFIGURATION:
    case HK_CHR_SUPPORTED_AUDIO_STREAMING_CONFIGURATION:
    case HK_CHR_SUPPORTED_RTP_CONFIGURATION:
    case HK_CHR_SETUP_ENDPOINTS:
    case HK_CHR_SELECTED_RTP_STREAM_CONFIGURATION:
    case HK_CHR_PAIR_SETUP:
    case HK_CHR_PAIR_VERIFY:
    case HK_CHR_PAIRING_PAIRINGS:
    case HK_CHR_SERVICE_SIGNATURE:
        return HK_FORMAT_TLV8;
    // case HK_CHR:
    //     return HK_FORMAT_DATA
    default:
        HK_LOGE("Could not find format for type %X", chr_type);
        return HK_FORMAT_UNKNOWN;
    }
}

uint16_t hk_chrs_properties_get_prop(hk_chr_types_t chr_type)
{
    switch (chr_type)
    {
    case HK_CHR_FIRMWARE_REVISION:
    case HK_CHR_HARDWARE_REVISION:
    case HK_CHR_MANUFACTURER:
    case HK_CHR_MODEL:
    case HK_CHR_NAME:
    case HK_CHR_SERIAL_NUMBER:
    case HK_CHR_SERVICE_SIGNATURE:
    case HK_CHR_VERSION:
        return HK_CHR_PROP_SUPPORTS_SECURE_READS;

    case HK_CHR_IDENTIFY:
        return HK_CHR_PROP_SUPPORTS_SECURE_WRITES;

    case HK_CHR_PAIR_SETUP:
    case HK_CHR_PAIR_VERIFY:
    case HK_CHR_PAIRING_PAIRINGS:
        return HK_CHR_PROP_SUPPORTS_READ | HK_CHR_PROP_SUPPORTS_WRITE;
        
    case HK_CHR_PAIRING_FEATURES:
        return HK_CHR_PROP_SUPPORTS_READ;

    case HK_CHR_ON:
    case HK_CHR_ACTIVE:
    case HK_CHR_STATUS_ACTIVE:
    case HK_CHR_TARGET_HEATING_COOLING_STATE:
    case HK_CHR_TARGET_HEATER_COOLER_STATE:
    return HK_CHR_PROP_SUPPORTS_SECURE_READS 
        | HK_CHR_PROP_SUPPORTS_SECURE_WRITES 
        | HK_CHR_PROP_NOTIFIES_EVENTS_CONNECTED_STATE
        | HK_CHR_PROP_NOTIFIES_EVENTS_DISCONNECTED_STATE
        | HK_CHR_PROP_SUPPORTS_BROADCAST_NOTIFY;

    case HK_CHR_TARGET_TEMPERATURE:
    case HK_CHR_COOLING_THRESHOLD_TEMPERATURE:
    case HK_CHR_HEATING_THRESHOLD_TEMPERATURE:
    case HK_CHR_TEMPERATURE_DISPLAY_UNITS:
    case HK_CHR_SWING_MODE:
    case HK_CHR_ROTATION_SPEED:
    case HK_CHR_LOCK_PHYSICAL_CONTROLS:
        return HK_CHR_PROP_SUPPORTS_SECURE_READS 
        | HK_CHR_PROP_SUPPORTS_SECURE_WRITES 
        | HK_CHR_PROP_NOTIFIES_EVENTS_CONNECTED_STATE
        | HK_CHR_PROP_NOTIFIES_EVENTS_DISCONNECTED_STATE;

    case HK_CHR_CURRENT_HEATING_COOLING_STATE:
    case HK_CHR_CURRENT_HEATER_COOLER_STATE:
    case HK_CHR_CURRENT_TEMPERATURE:
    case HK_CHR_CURRENT_RELATIVE_HUMIDITY:
    case HK_CHR_MOTION_DETECTED:
    case HK_CHR_STATUS_LOW_BATTERY:
    case HK_CHR_BATTERY_LEVEL:
        return HK_CHR_PROP_SUPPORTS_SECURE_READS 
        | HK_CHR_PROP_NOTIFIES_EVENTS_CONNECTED_STATE
        | HK_CHR_PROP_NOTIFIES_EVENTS_DISCONNECTED_STATE
        | HK_CHR_PROP_SUPPORTS_BROADCAST_NOTIFY;

    case HK_CHR_ADMINISTRATOR_ONLY_ACCESS: //todo: set properties for all characteristics
    case HK_CHR_AUDIO_FEEDBACK:
    case HK_CHR_OBSTRUCTION_DETECTED:
    case HK_CHR_OUTLET_IN_USE:
    case HK_CHR_HOLD_POSITION:
    case HK_CHR_MUTE:
    case HK_CHR_NIGHT_VISION:
    case HK_CHR_CURRENT_DOOR_STATE:
    case HK_CHR_LOCK_CURRENT_STATE:
    case HK_CHR_LOCK_LAST_KNOWN_ACTION:
    case HK_CHR_LOCK_MANAGEMENT_AUTO_SECURITY_TIMEOUT:
    case HK_CHR_LOCK_TARGET_STATE:
    case HK_CHR_TARGET_DOORSTATE:
    case HK_CHR_AIR_PARTICULATE_SIZE:
    case HK_CHR_SECURITY_SYSTEM_CURRENT_STATE:
    case HK_CHR_SECURITY_SYSTEM_TARGET_STATE:
    case HK_CHR_CARBON_MONOXIDE_DETECTED:
    case HK_CHR_CONTACT_SENSOR_STATE:
    case HK_CHR_CURRENT_POSITION:
    case HK_CHR_LEAK_DETECTED:
    case HK_CHR_OCCUPANCY_DETECTED:
    case HK_CHR_POSITION_STATE:
    case HK_CHR_PROGRAMMABLE_SWITCH_EVENT:
    case HK_CHR_SMOKE_DETECTED:
    case HK_CHR_STATUS_FAULT:
    case HK_CHR_STATUS_JAMMED:
    case HK_CHR_STATUS_TAMPERED:
    case HK_CHR_TARGET_POSITION:
    case HK_CHR_SECURITY_SYSTEM_ALARM_TYPE:
    case HK_CHR_CHARGING_STATE:
    case HK_CHR_CARBON_DIOXIDE_DETECTED:
    case HK_CHR_AIR_QUALITY:
    case HK_CHR_VOLUME:
    case HK_CHR_CURRENT_AIR_PURIFIER_STATE:
    case HK_CHR_CURRENT_SLAT_STATE:
    case HK_CHR_SLAT_TYPE:
    case HK_CHR_FILTER_CHANGE_INDICATION:
    case HK_CHR_RESET_FILTER_INDICATION:
    case HK_CHR_TARGET_AIR_PURIFIER_STATE:
    case HK_CHR_TARGET_FAN_STATE:
    case HK_CHR_CURRENT_FAN_STATE:
    case HK_CHR_SERVICE_LABEL_INDEX:
    case HK_CHR_SERVICE_LABEL_NAMESPACE:
    case HK_CHR_ACCESSORY_FLAGS:
    case HK_CHR_COLOR_TEMPERATURE:
    case HK_CHR_BRIGHTNESS:
    case HK_CHR_ROTATION_DIRECTION:
    case HK_CHR_CURRENT_HORIZONTAL_TILT_ANGLE:
    case HK_CHR_CURRENT_VERTICAL_TILT_ANGLE:
    case HK_CHR_TARGET_HORIZONTAL_TILT_ANGLE:
    case HK_CHR_TARGET_VERTICAL_TILT_ANGLE:
    case HK_CHR_CURRENT_TILT_ANGLE:
    case HK_CHR_TARGET_TILT_ANGLE:
    case HK_CHR_HUE:
    case HK_CHR_SATURATION:
    case HK_CHR_AIR_PARTICULATE_DENSITY:
    case HK_CHR_CURRENT_AMBIENT_LIGHT_LEVEL:
    case HK_CHR_CARBON_MONOXIDE_LEVEL:
    case HK_CHR_CARBON_MONOXIDE_PEAK_LEVEL:
    case HK_CHR_CARBON_DIOXIDE_LEVEL:
    case HK_CHR_CARBON_DIOXIDE_PEAK_LEVEL:
    case HK_CHR_OPTICAL_ZOOM:
    case HK_CHR_DIGITAL_ZOOM:
    case HK_CHR_IMAGE_ROTATION:
    case HK_CHR_IMAGE_MIRRORING:
    case HK_CHR_FILTER_LIFE_LEVEL:
    case HK_CHR_OZONE_DENSITY:
    case HK_CHR_NITROGEN_DIOXIDE_DENSITY:
    case HK_CHR_SULPHUR_DIOXIDE_DENSITY:
    case HK_CHR_PM25_DENSITY:
    case HK_CHR_PM10_DENSITY:
    case HK_CHR_VOC_DENSITY:
    case HK_CHR_TARGET_RELATIVE_HUMIDITY:
    case HK_CHR_LOCK_CONTROL_POINT:
    case HK_CHR_LOGS:
    case HK_CHR_STREAMING_STATUS:
    case HK_CHR_SUPPORTED_VIDEO_STREAMING_CONFIGURATION:
    case HK_CHR_SUPPORTED_AUDIO_STREAMING_CONFIGURATION:
    case HK_CHR_SUPPORTED_RTP_CONFIGURATION:
    case HK_CHR_SETUP_ENDPOINTS:
    case HK_CHR_SELECTED_RTP_STREAM_CONFIGURATION:
    default:
        HK_LOGE("Could not return characteristic properties for type %X", chr_type);
        return -1;
    }
}

#define desc_valid_range(desc, t, min, max) { \
 (desc)->type = HK_DESC_VALID_RANGE; \
 t *data = malloc(sizeof(t) * 2); \
 data[0] = (min); \
 data[1] = (max); \
 (desc)->data.ptr = (char *)data; \
 (desc)->data.size = sizeof(t) * 2; \
}

#define desc_step_value(desc, t, v) { \
 (desc)->type = HK_DESC_STEP_VALUE; \
 t *data = malloc(sizeof(t)); \
 data[0] = (v); \
 (desc)->data.ptr = (char *)data; \
 (desc)->data.size = sizeof(t); \
}

#define desc_valid_values(desc, t, v, num) { \
 (desc)->type = HK_DESC_VALID_VALUES; \
 (desc)->data.ptr = malloc(sizeof(t) * num); \
 memcpy((desc)->data.ptr, v, sizeof(t) * num); \
 (desc)->data.size = sizeof(t) * num; \
}

hk_desc_t *hk_chrs_properties_descriptors(hk_chr_types_t chr_type, size_t *result_len)
{
    hk_desc_t *descs = NULL;
    *result_len = 0;

    switch (chr_type)
    {
    case HK_CHR_TARGET_HEATER_COOLER_STATE:
        descs = malloc(3 * sizeof(hk_desc_t));
        desc_valid_range(descs + 0, uint8_t, 0, 2);
        desc_step_value(descs + 1, uint8_t, 1);
        // TODO: configure the heat/cool/heat-or-cool here
        //desc_valid_values(descs + 2, uint8_t, "\0\1\2", 3);
        desc_valid_values(descs + 2, uint8_t, "\1", 1);
        *result_len = 3;
        break;
    case HK_CHR_CURRENT_HEATER_COOLER_STATE:
        descs = malloc(3 * sizeof(hk_desc_t));
        desc_valid_range(descs + 0, uint8_t, 0, 3);
        desc_step_value(descs + 1, uint8_t, 1);
        desc_valid_values(descs + 2, uint8_t, "\0\1\2\3", 4);
        *result_len = 3;
        break;
    case HK_CHR_HEATING_THRESHOLD_TEMPERATURE:
        descs = malloc(2 * sizeof(hk_desc_t));
        desc_valid_range(descs + 0, float, 0, 25);
        desc_step_value(descs + 1, float, 0.1);
        *result_len = 2;
        break;
    default:
        break;
    }

    return descs;
}