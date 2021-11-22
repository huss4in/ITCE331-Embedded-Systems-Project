// Unity Test Framework
#include <unity.h>
#include <Arduino.h>

// Classes
#include "Lists.h"
#include "CPU.h"

// Tests
#include "tests/queue.h"
#include "tests/CPU.h"

// // Other Tests
// #include "Lists/LinkedList.h"
// #include "tests/other.h"

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    test_queue(); // Run queue tests
    test_cpu();   // Run CPU tests

    // // test_other(); // Run other tests

    UNITY_END(); // End unity testing
}

void loop()
{
}