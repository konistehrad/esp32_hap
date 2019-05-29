#pragma once

#include <stdlib.h>
#include <stdbool.h>

void hk_mdns_init(const char *name, size_t category, size_t config_version);
void hk_mdns_update_paired(bool initial);
