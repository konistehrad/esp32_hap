#pragma once

#include "utils/hk_mem.h"
#include "hk_session.h"

#include <esp_err.h>

esp_err_t hk_com_start(
    int port, 
    esp_err_t (*receiver)(hk_session_t *connection, hk_mem* data)
);

esp_err_t hk_com_send_data(hk_session_t *connection, hk_mem *data_to_send);

void hk_com_kill_sessions_of_device(hk_session_t *session);
