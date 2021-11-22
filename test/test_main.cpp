// Unity Test Framework
#include <unity.h>

// Classes
#include "Queue.h"
#include "CPU/CPU.h"

// Tests
#include "tests/queue.h"
#include "tests/CPU.h"
#include "tests/other.h"

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    test_queue(); // Run queue tests
    test_cpu();   // Run CPU tests
    test_other(); // Run other tests

    UNITY_END(); // End unity testing
}

void loop()
{
}