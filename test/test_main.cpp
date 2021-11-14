#include <unity.h>

#include "Queue.h"

#include "tests/queue.h"
#include "tests/CPU.h"

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    test_queue();   // Run queue tests
    test_process(); // Run process tests

    UNITY_END(); // End unity testing
}

void loop()
{
}