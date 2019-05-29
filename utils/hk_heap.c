#include "hk_heap.h"

#include "hk_logging.h"

#include <stdio.h>
#include <esp_heap_trace.h>

#include <freertos/FreeRTOS.h>
#include <freertos/portable.h>

#define NUM_RECORDS 100
static heap_trace_record_t trace_record[NUM_RECORDS]; // This buffer must be in internal RAM
int heap_size_start = -1;

void hk_heap_log()
{
    HK_LOGI("Current free heap: %d", xPortGetFreeHeapSize());
}

void hk_heap_check_start()
{
    //doing a sprintf which allocates mem on the heap the first time it is used, which might lead to false positives later
    char str[1];
    sprintf(str, "%1.0f", 1.0);
    
    HK_LOGD("Starting heap check with: %d", xPortGetFreeHeapSize());
    if (heap_size_start < 0)
    {
        heap_trace_init_standalone(trace_record, NUM_RECORDS);
    }
    heap_size_start = xPortGetFreeHeapSize();
    ESP_ERROR_CHECK(heap_trace_start(HEAP_TRACE_LEAKS));
}

bool hk_heap_check_end()
{
    ESP_ERROR_CHECK(heap_trace_stop());
    int heap_size_end = xPortGetFreeHeapSize();
    if (heap_size_start > heap_size_end)
    {
        heap_trace_dump();
        HK_LOGE("Lost heap: %d => %d", heap_size_start, heap_size_end);
        return false;
    }

    return true;
}