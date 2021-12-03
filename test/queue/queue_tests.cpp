#include <Arduino.h>
#include <unity.h>

#include "Lists.h"

// #define VERBOSE true

#include "queue_tests.h"

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    // Test push
    RUN_TEST(test_queue_push);
    RUN_TEST(test_queue_push_full);

    // Test pop
    RUN_TEST(test_queue_pop);
    RUN_TEST(test_queue_pop_empty);

    // Test pop index
    RUN_TEST(test_queue_pop_index);
    RUN_TEST(test_queue_pop_index_middle);
    RUN_TEST(test_queue_pop_index_end);

    // Test front & back
    RUN_TEST(test_queue_front_back);

    // Test size
    RUN_TEST(test_queue_size);

    UNITY_END(); // End unity testing
}

void loop()
{
}