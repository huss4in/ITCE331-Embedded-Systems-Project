#include <Arduino.h>
#include <unity.h>

#include "Lists.h"

// #define VERBOSE true

#include "stack_tests.h"

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    // Test push
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_push_full);

    // Test pop
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_pop_empty);

    // Test front & back
    RUN_TEST(test_stack_front_back);

    // Test size
    RUN_TEST(test_stack_size);

    // Test pop index
    RUN_TEST(test_stack_pop_index);
    RUN_TEST(test_stack_pop_index_middle);
    RUN_TEST(test_stack_pop_index_end);

    UNITY_END(); // End unity testing
}

void loop()
{
}