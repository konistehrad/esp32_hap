#include "crypto/hk_chacha20poly1305.h"
#include "utils/hk_logging.h"
#include "utils/hk_mem.h"
#include "utils/hk_store.h"
#include "utils/hk_util.h"
#include "hk_html_parser.h"
#include "hk_com.h"
#include "hk_accessories.h"
#include "hk_pair_setup.h"
#include "hk_pair_verify.h"
#include "hk_pairings.h"
#include "hk_session.h"
#include "hk_characteristics.h"
#include "hk_encryption.h"
#include "hk_html.h"

#include <stdbool.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <esp_http_server.h>

void hk_server_handle(hk_session_t *session)
{
    //HK_LOGD("%d - Handling %s, %d", session->socket, session->request->url->ptr, session->request->method);

    if (hk_mem_cmp_str(session->request->url, "/pair-setup") && HK_SESSION_HTML_METHOD_POST == session->request->method)
    {
        hk_pair_setup(session);
    }
    else if (hk_mem_cmp_str(session->request->url, "/pair-verify") && HK_SESSION_HTML_METHOD_POST == session->request->method)
    {
        hk_pair_verify(session);
    }
    else if (hk_mem_cmp_str(session->request->url, "/accessories") && HK_SESSION_HTML_METHOD_GET == session->request->method)
    {
        hk_accessories_get(session);
    }
    else if (hk_mem_cmp_str(session->request->url, "/characteristics") && HK_SESSION_HTML_METHOD_GET == session->request->method)
    {
        hk_characteristics_get(session);
    }
    else if (hk_mem_cmp_str(session->request->url, "/characteristics") && HK_SESSION_HTML_METHOD_PUT == session->request->method)
    {
        hk_characteristics_put(session);
    }
    else if (hk_mem_cmp_str(session->request->url, "/pairings") && HK_SESSION_HTML_METHOD_POST == session->request->method)
    {
        hk_pairings(session);
    }
    else if (hk_mem_cmp_str(session->request->url, "/identify") && HK_SESSION_HTML_METHOD_POST == session->request->method)
    {
        hk_characteristics_identify(session);
    }
    else
    {
        HK_LOGE("Could not find handler for '%s' and method %d.", session->request->url->ptr, session->request->method);
        hk_html_response_send_empty(session, HK_HTML_404);
        session->should_close = true;
    }
}

esp_err_t hk_server_receiver(hk_session_t *session, hk_mem *data)
{
    hk_session_clean(session);
    hk_mem *decrypted = hk_mem_create();
    hk_mem *response = hk_mem_create();

    // encryption decrypts the data
    esp_err_t ret = hk_encryption_preprocessor(session, data, decrypted);
    if (ret != ESP_OK)
    {
        HK_LOGE("Could not pre process received data of socket %d.", session->socket);
    }

    // html parses the content of request data and calls the configured handler
    ret = hk_html_parser_parse(decrypted, session);
    if (ret != ESP_OK)
    {
        HK_LOGE("Could not process received data of socket %d.", session->socket);
    }

    hk_server_handle(session);

    hk_mem_free(decrypted);
    hk_mem_free(response);

    return ret;
}

void hk_server_start(void)
{
    hk_com_start(5556, hk_server_receiver);
}