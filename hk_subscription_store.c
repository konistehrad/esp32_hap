#include "hk_subscription_store.h"

#include "utils/hk_ll.h"
#include "utils/hk_logging.h"
#include <stdbool.h>

typedef struct
{
    hk_characteristic_t *characteristic;
    hk_session_t **sessions;
} hk_subscription_t;

hk_subscription_t *subscriptions = NULL;

hk_subscription_t *hk_subscription_store_get_subscription(hk_characteristic_t *characteristic)
{
    hk_subscription_t *subscription = NULL;

    hk_ll_foreach(subscriptions, current_subscription)
    {
        if (current_subscription->characteristic == characteristic)
        {
            subscription = current_subscription;
        }
    }

    return subscription;
}

hk_session_t **hk_subscription_store_get_sessions(hk_characteristic_t *characteristic)
{
    hk_subscription_t *subscription = hk_subscription_store_get_subscription(characteristic);
    if (subscription == NULL)
    {
        return NULL;
    }

    return subscription->sessions;
}

void hk_subscription_store_add_session(hk_characteristic_t *characteristic, hk_session_t *session)
{
    hk_subscription_t *subscription = hk_subscription_store_get_subscription(characteristic);

    if (subscription == NULL)
    {
        HK_LOGD("No subscriptions found for characteristic, creating new list.");
        subscription = subscriptions = hk_ll_new(subscriptions);
        subscription->characteristic = characteristic;
        subscription->sessions = NULL;
    }
    else
    {
        hk_ll_foreach(subscription->sessions, current_session)
        {
            if (*current_session == session)
            {
                HK_LOGD("Subscription exists, doing nothing.");
                return;
            }
        }
    }

    HK_LOGD("Adding session %x to subscription list of %x.", (uint)session, (uint)characteristic);
    subscription->sessions = hk_ll_new(subscription->sessions);
    *subscription->sessions = session;
}

void hk_subscription_store_remove_session(hk_session_t *session)
{
    hk_ll_foreach(subscriptions, current_subscription)
    {
        for (hk_session_t **current_session = current_subscription->sessions; current_session != NULL;)
        {
            if (*current_session == session)
            {
                hk_session_t **next = hk_ll_next(current_session);
                current_subscription->sessions = hk_ll_remove(current_subscription->sessions, current_session);
                current_session = next;
            }
            else
            {
                current_session = hk_ll_next(current_session);
            }
        }
    }
}

void hk_subscription_store_free()
{
    hk_ll_foreach(subscriptions, subscription_item)
    {
        hk_ll_free(subscription_item->sessions);
    }

    hk_ll_free(subscriptions);
    subscriptions = NULL;
}