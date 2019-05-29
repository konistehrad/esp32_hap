#include "unity.h"

#include "../utils/hk_logging.h"
#include "../utils/hk_mem.h"
#include "../utils/hk_heap.h"

#include "../hk_html_parser.h"

TEST_CASE("Html parser: get query value", "[html]")
{

    hk_heap_check_start();

    hk_mem *query = hk_mem_create();
    hk_mem_append_string(query, "id=2.8");
    hk_mem_append_string_terminator(query);
    hk_mem *ids = hk_mem_create();

    hk_html_parser_get_query_value(query, "id", ids);
    hk_mem_log("Ids from query: %s", ids);
    TEST_ASSERT_GREATER_THAN_INT(0, ids->size);
    hk_mem_free(query);
    hk_mem_free(ids);
    
    TEST_ASSERT_TRUE(hk_heap_check_end());
}