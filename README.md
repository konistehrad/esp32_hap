# esp32-homekit
ESP-32 implementation of Apple Homekit Accessory Protocol(HAP)

## Installation
1. Setup esp-idf development environment: https://docs.espressif.com/projects/esp-idf/en/latest/get-started/
3. Install wolfssl
3.1. Clone wolfssl: https://github.com/wolfSSL/wolfssl
3.2. Install wolfssl into esp-idf:https://github.com/wolfSSL/wolfssl/blob/master/IDE/Espressif/ESP-IDF/README.md
3.2.1. Open terminal with esp env vars set
3.2.2. Execute setup.sh from <path to wolfssl>/IDE/Espressif/ESP-IDF
3.3: Adapt user_settings.h in <path to esp idf>/components/wolfssl/include/user_settings.h by appending the following lines:
#include <esp_system.h>
static inline int hwrand_generate_block(uint8_t *buf, size_t len) {
    int i;
    for (i=0; i+4 < len; i+=4) {
        *((uint32_t*)buf) = esp_random();
        buf += 4;
    }
    if (i < len) {
        uint32_t r = esp_random();
        while (i < len) {
            *buf++ = r;
            r >>= 8;
            i++;
        }
    }

    return 0;
}
#define CUSTOM_RAND_GENERATE_BLOCK hwrand_generate_block
4. Create an application and init it

## Debugging
### How to WireShark the IOs Device
1. Connect device by USB
2. Get your UDID: http://whatsmyudid.com/
3. Check your network devices: ifconfig -l
4. Start capturing: rvictl -s <UDID>
5. Check your network devices again: ifconfig -l
6. Open WireShark
7. Start capturing on the new interface (normally rvi0)
8. Filter for http

### Debug mDNS/Bonjour/Zeroconf
HomeKit uses the service type of '_hap._tcp' on the 'local.' domain, so you can query for HomeKit devices as such:

$ dns-sd -Z _hap._tcp local.

For HomeKit hubs, look for the service type of _homekit._tcp:

$ dns-sd -Z _homekit._tcp local.

## Troubleshooting
- To be able to upload to the EP-WROOM-32 when connected to a breadboard, you may need a 10K (or so) pull-down resistor between RX0 and GND.
- In case you cannot find your device, it may be a problem with your router: https://jlian.co/post/reliable-homekit/