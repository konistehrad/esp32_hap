#include "hk_accessories.h"
#include "utils/hk_logging.h"
#include "utils/hk_ll.h"
#include "hk_accessories_serializer.h"
#include "hk_accessories_store.h"
#include "hk_html.h"

void hk_accessories_get(hk_session_t *session)
{
    hk_accessories_serializer_accessories(session->response->content);
    session->response->content_type = HK_SESSION_CONTENT_JSON;
    HK_LOGD("%d - Returning accessories.", session->socket);
    hk_session_send(session);
}