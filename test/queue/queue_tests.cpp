#include <Arduino.h>
#include <unity.h>

#include "DataStructure.h"

#define VERBOSE true

#define SIZE 10

// ? Test Queue push normal
void test_queue_push()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        bool result = queue.push(i);

#if VERBOSE
        queue.printItems();
#endif

        TEST_ASSERT_EQUAL(true, result);
    }
}

// * Push help function
void populate_queue(DataStructure::Queue<int> *queue)
{
    for (uint8_t i = 1; i <= SIZE; i++)
        queue->push(i);

#if VERBOSE
    queue->print();
#endif
}

// ? Test Queue front and back
void test_queue_front_back()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    for (uint8_t i = 1; i < SIZE; i++)
    {
        queue.push(i);

#if VERBOSE
        queue.printItems();
#endif

        TEST_ASSERT_EQUAL(1, queue.front());

        TEST_ASSERT_EQUAL(i, queue.back());
    }
}

// ? Test Queue push when queue is full
void test_queue_push_full()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue);

    bool result = queue.push(SIZE + 1);

#if VERBOSE
    queue.printItems();
#endif

    TEST_ASSERT_EQUAL(false, result);
}

// ? Test Queue size
void test_queue_size()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

#if VERBOSE
    queue.print();
#endif

    TEST_ASSERT_EQUAL(0, queue.size());
    queue.push(10);

#if VERBOSE
    queue.print();
#endif

    TEST_ASSERT_EQUAL(1, queue.size());
    queue.push(11);

#if VERBOSE
    queue.print();
#endif

    TEST_ASSERT_EQUAL(2, queue.size());
    queue.pop();

#if VERBOSE
    queue.print();
#endif

    TEST_ASSERT_EQUAL(1, queue.size());
    queue.pop();

#if VERBOSE
    queue.print();
#endif

    TEST_ASSERT_EQUAL(0, queue.size());
    queue.pop();

#if VERBOSE
    queue.print();
#endif

    TEST_ASSERT_EQUAL(0, queue.size());
}

// ? Test Queue pop normal
void test_queue_pop()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
#if VERBOSE
        queue.printItems();
#endif

        TEST_ASSERT_EQUAL(i, queue.pop());

        TEST_ASSERT_EQUAL(SIZE - i, queue.size());
    }
}

// ? Test Queue pop when queue is empty
void test_queue_pop_empty()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

#if VERBOSE
    queue.printHeader();
#endif

    int result = queue.pop();

#if VERBOSE
    queue.printItems();
#endif

    TEST_ASSERT_EQUAL(0, result);

    queue.push(1);

#if VERBOSE
    queue.printItems();
#endif

    queue.pop();

#if VERBOSE
    queue.printItems();
#endif

    TEST_ASSERT_EQUAL(0, queue.pop());
}

// ? Test Queue pop in the middle of queue
void test_queue_pop_middle()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue); // H: 1 <-- 2 <-- 3 <-- 4 <-- 5 :T

    int result = queue.pop(2); // 3

#if VERBOSE
    queue.printItems();
#endif

    TEST_ASSERT_EQUAL(3, result); // H: 1 <-- 2 <-- 4 <-- 5 :T

    result = queue.pop(2); // 4

#if VERBOSE
    queue.printItems();
#endif

    TEST_ASSERT_EQUAL(4, result); // H: 1 <-- 2 <-- 5 :T

    result = queue.pop(1); // 2

#if VERBOSE
    queue.printItems();
#endif

    TEST_ASSERT_EQUAL(2, result); // H: 1 <-- 5 :T

    TEST_ASSERT_EQUAL(1, queue.front());
    TEST_ASSERT_EQUAL(SIZE, queue.back());
    TEST_ASSERT_EQUAL(SIZE - 3, queue.size());

#if VERBOSE
    queue.printItems();
#endif
}

// ? Test Queue pop in the middle of queue
void test_queue_pop_end()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue);

    TEST_ASSERT_EQUAL(SIZE, queue.pop(SIZE - 1));

#if VERBOSE
    queue.printItems();
#endif
}

// ? Test Queue Node size()
void test_queue_node_size()
{
    DataStructure::Queue<int> q1 = DataStructure::Queue<int>();

#if VERBOSE
    q1.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(int) + sizeof(int), q1.itemSize());

    DataStructure::Queue<uint32_t> q2 = DataStructure::Queue<uint32_t>();

#if VERBOSE
    q2.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(uint32_t) + sizeof(int), q2.itemSize());
}

// ? Test Queue Copy Constructor
void test_queue_copy_constructor()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue);

    DataStructure::Queue<int> queue2 = queue;

#if VERBOSE
    queue2.print();
#endif

    TEST_ASSERT_EQUAL(queue.size(), queue2.size());
    TEST_ASSERT_EQUAL(queue.front(), queue2.front());
    TEST_ASSERT_EQUAL(queue.back(), queue2.back());
};

// ? Test Queue times of function
void test_queue_times()
{
    unsigned long start, end;

    Serial.println("Tessing Queue APIs times...");
    Serial.println("---");

    start = micros();

    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    end = micros();

    Serial.println("Queue Constructor: " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    for (uint16_t i = 1; i <= SIZE; i++)
        queue.push(i);

    end = micros();

    Serial.println("Queue.push(): " + String((end - start) / SIZE) + " microseconds" + "\n---");

    start = micros();

    for (uint16_t i = 1; i <= SIZE; i++)
        queue.pop(i);

    end = micros();

    Serial.println("Queue.pop(): " + String((end - start) / SIZE) + " microseconds" + "\n---");

    start = micros();

    queue.front();

    end = micros();

    Serial.println("Queue.front(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    queue.back();

    end = micros();

    Serial.println("Queue.back(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    queue.size();

    end = micros();

    Serial.println("Queue.size(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    queue.empty();

    end = micros();

    Serial.println("Queue.empty(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    queue.full();

    end = micros();

    Serial.println("Queue.full(): " + String(end - start) + " microseconds" + "\n---");

    for (uint16_t i = 1; i <= SIZE; i++)
        queue.push(i);

    start = micros();

    DataStructure::Queue<int> q2 = queue;

    end = micros();

    Serial.println("Queue Copy Constructor: " + String(end - start) + " microseconds" + "\n---");

    Serial.println("Queue Memory Usage: \n---");

    q2.print();
};

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    RUN_TEST(test_queue_push);
    RUN_TEST(test_queue_push_full);

    RUN_TEST(test_queue_front_back);
    RUN_TEST(test_queue_size);

    RUN_TEST(test_queue_pop);
    RUN_TEST(test_queue_pop_empty);
    RUN_TEST(test_queue_pop_middle);
    RUN_TEST(test_queue_pop_end);

    RUN_TEST(test_queue_node_size);

    RUN_TEST(test_queue_copy_constructor);

    RUN_TEST(test_queue_times);

    UNITY_END(); // End unity testing
}

void loop()
{
}