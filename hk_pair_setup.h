#pragma once

#include "utils/hk_mem.h"
#include "utils/hk_tlv.h"
#include "hk_session.h"

#include <esp_err.h>
#include <stdlib.h>

void hk_pair_setup(hk_session_t *session_context);
