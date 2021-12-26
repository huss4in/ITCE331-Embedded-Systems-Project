#include <Arduino.h>
#include <unity.h>

#include "DataStructure.h"

#define VERBOSE true

#define SIZE 10

// ? Test CircularQueue push normal
void test_circularqueue_push()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        bool result = circularqueue.push(i);

#if VERBOSE
        circularqueue.printItems();
#endif

        TEST_ASSERT_EQUAL(true, result);
    }
}

// * Push help function
void populate_circularqueue(DataStructure::CircularQueue<int> *circularqueue)
{
    for (uint8_t i = 1; i <= SIZE; i++)
        circularqueue->push(i);

#if VERBOSE
    circularqueue->print();
#endif
}

// ? Test CircularQueue front and back
void test_circularqueue_front_back()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        circularqueue.push(i);

#if VERBOSE
        circularqueue.printItems();
#endif

        TEST_ASSERT_EQUAL(1, circularqueue.front());

        TEST_ASSERT_EQUAL(i, circularqueue.back());
    }
}

// ? Test CircularQueue push when circularqueue is full
void test_circularqueue_push_full()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    populate_circularqueue(&circularqueue);

    bool result = circularqueue.push(SIZE + 1);

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(true, result);

    TEST_ASSERT_EQUAL(2, circularqueue.front());
}

// ? Test CircularQueue size
void test_circularqueue_size()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

#if VERBOSE
    circularqueue.print();
#endif

    TEST_ASSERT_EQUAL(0, circularqueue.size());
    circularqueue.push(1);

#if VERBOSE
    circularqueue.print();
#endif

    TEST_ASSERT_EQUAL(1, circularqueue.size());
    circularqueue.push(2);

#if VERBOSE
    circularqueue.print();
#endif

    TEST_ASSERT_EQUAL(2, circularqueue.size());
    circularqueue.pop();

#if VERBOSE
    circularqueue.print();
#endif

    TEST_ASSERT_EQUAL(1, circularqueue.size());
    circularqueue.pop();

#if VERBOSE
    circularqueue.print();
#endif

    TEST_ASSERT_EQUAL(0, circularqueue.size());
    circularqueue.pop();

#if VERBOSE
    circularqueue.print();
#endif

    TEST_ASSERT_EQUAL(0, circularqueue.size());
}

// ? Test CircularQueue pop normal
void test_circularqueue_pop()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    populate_circularqueue(&circularqueue);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        int result = circularqueue.pop();

#if VERBOSE
        circularqueue.printItems();
#endif

        TEST_ASSERT_EQUAL(i, result);

        TEST_ASSERT_EQUAL(SIZE - i, circularqueue.size());
    }

    populate_circularqueue(&circularqueue);

    int result = circularqueue.push(SIZE + 1);

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(true, result);

    TEST_ASSERT_EQUAL(2, circularqueue.front());

    TEST_ASSERT_EQUAL(SIZE + 1, circularqueue.back());

    TEST_ASSERT_EQUAL(SIZE, circularqueue.size());

    TEST_ASSERT_EQUAL(2, circularqueue.pop());

    TEST_ASSERT_EQUAL(SIZE - 1, circularqueue.size());
}

// ? Test CircularQueue pop when circularqueue is empty
void test_circularqueue_pop_empty()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

#if VERBOSE
    circularqueue.printHeader();
#endif

    int result = circularqueue.pop();

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(0, result);

    circularqueue.push(1);

#if VERBOSE
    circularqueue.printItems();
#endif

    circularqueue.pop();

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(0, circularqueue.pop());
}

// ? Test CircularQueue pop in the middle of circularqueue
void test_circularqueue_pop_middle()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    populate_circularqueue(&circularqueue); // H: 1 <-- 2 <-- 3 <-- 4 <-- 5 :T

    int result = circularqueue.pop(2); // 3

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(3, result); // H: 1 <-- 2 <-- 4 <-- 5 :T

    result = circularqueue.pop(2); // 4

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(4, result); // H: 1 <-- 2 <-- 5 :T

    result = circularqueue.pop(1); // 2

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(2, result); // H: 1 <-- 5 :T

    TEST_ASSERT_EQUAL(1, circularqueue.front());
    TEST_ASSERT_EQUAL(SIZE, circularqueue.back());
    TEST_ASSERT_EQUAL(SIZE - 3, circularqueue.size());

#if VERBOSE
    circularqueue.printItems();
#endif
}

// ? Test CircularQueue pop in the middle of circularqueue
void test_circularqueue_pop_end()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    populate_circularqueue(&circularqueue);

    int result = circularqueue.pop(SIZE - 1);

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(SIZE, result);

    result = circularqueue.push(SIZE);

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(true, result);

    TEST_ASSERT_EQUAL(1, circularqueue.front());
    TEST_ASSERT_EQUAL(SIZE, circularqueue.back());

    result = circularqueue.push(SIZE + 1);

#if VERBOSE
    circularqueue.printItems();
#endif

    TEST_ASSERT_EQUAL(true, result);

    TEST_ASSERT_EQUAL(2, circularqueue.front());
    TEST_ASSERT_EQUAL(SIZE + 1, circularqueue.back());
}

// ? Test CircularQueue Node size()
void test_circularqueue_node_size()
{
    DataStructure::CircularQueue<int> q1 = DataStructure::CircularQueue<int>(SIZE);

#if VERBOSE
    q1.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(int) + sizeof(int), q1.itemSize());

    DataStructure::CircularQueue<uint32_t> q2 = DataStructure::CircularQueue<uint32_t>(SIZE);

#if VERBOSE
    q2.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(uint32_t) + sizeof(int), q2.itemSize());
}

// ? Test CircularQueue Copy Constructor
void test_circularqueue_copy_constructor()
{
    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    populate_circularqueue(&circularqueue);

    DataStructure::CircularQueue<int> circularqueue2 = circularqueue;

#if VERBOSE
    circularqueue2.print();
#endif

    TEST_ASSERT_EQUAL(circularqueue.size(), circularqueue2.size());
    TEST_ASSERT_EQUAL(circularqueue.front(), circularqueue2.front());
    TEST_ASSERT_EQUAL(circularqueue.back(), circularqueue2.back());
};

// ? Test CircularQueue times of function
void test_circularqueue_times()
{
    unsigned long start, end;

    Serial.println("Tessing CircularQueue APIs times...");
    Serial.println("---");

    start = micros();

    DataStructure::CircularQueue<int> circularqueue = DataStructure::CircularQueue<int>(SIZE);

    end = micros();

    Serial.println("CircularQueue Constructor: " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    for (uint16_t i = 1; i <= SIZE; i++)
        circularqueue.push(i);

    end = micros();

    Serial.println("CircularQueue.push(): " + String((end - start) / SIZE) + " microseconds" + "\n---");

    start = micros();

    for (uint16_t i = 1; i <= SIZE; i++)
        circularqueue.pop(i);

    end = micros();

    Serial.println("CircularQueue.pop(): " + String((end - start) / SIZE) + " microseconds" + "\n---");

    start = micros();

    circularqueue.front();

    end = micros();

    Serial.println("CircularQueue.front(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    circularqueue.back();

    end = micros();

    Serial.println("CircularQueue.back(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    circularqueue.size();

    end = micros();

    Serial.println("CircularQueue.size(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    circularqueue.empty();

    end = micros();

    Serial.println("CircularQueue.empty(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    circularqueue.full();

    end = micros();

    Serial.println("CircularQueue.full(): " + String(end - start) + " microseconds" + "\n---");

    for (uint16_t i = 1; i <= SIZE; i++)
        circularqueue.push(i);

    start = micros();

    DataStructure::CircularQueue<int> q2 = circularqueue;

    end = micros();

    Serial.println("CircularQueue Copy Constructor: " + String(end - start) + " microseconds" + "\n---");

    Serial.println("CircularQueue Memory Usage: \n---");

    q2.print();
};

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    RUN_TEST(test_circularqueue_push);
    RUN_TEST(test_circularqueue_front_back);
    RUN_TEST(test_circularqueue_push_full);

    RUN_TEST(test_circularqueue_size);

    RUN_TEST(test_circularqueue_pop);
    RUN_TEST(test_circularqueue_pop_empty);
    RUN_TEST(test_circularqueue_pop_middle);
    RUN_TEST(test_circularqueue_pop_end);

    RUN_TEST(test_circularqueue_node_size);

    RUN_TEST(test_circularqueue_copy_constructor);

    RUN_TEST(test_circularqueue_times);

    UNITY_END(); // End unity testing
}

void loop()
{
}