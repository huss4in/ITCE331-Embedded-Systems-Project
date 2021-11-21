#include <unity.h>

#include "Queue.h"
#include "CPU/CPU.h"

#include "tests/queue.h"
#include "tests/CPU.h"

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    test_queue(); // Run queue tests

    test_cpu(); // Run CPU tests

    UNITY_END(); // End unity testing
}

void loop()
{
}