#pragma once

#include "include/homekit_services.h"
#include "include/homekit_characteristics.h"
#include "utils/hk_mem.h"
#include "hk_session.h"

#include <esp_err.h>
#include <stdlib.h>
#include <cJSON.h>

void hk_accessories_get(hk_session_t *session_context);
