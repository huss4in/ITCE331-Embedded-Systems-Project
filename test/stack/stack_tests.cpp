#include <Arduino.h>
#include <unity.h>

#include "DataStructure.h"

#define VERBOSE true

#define SIZE 10

// * Push help function
void populate_stack(DataStructure::Stack<int> *stack)
{
    for (uint8_t i = 1; i <= SIZE; i++)
        stack->push(i);

#if VERBOSE
    stack->print();
#endif
}

// ? Test Stack push normal
void test_stack_push()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        TEST_ASSERT_EQUAL(true, stack.push(i));
#if VERBOSE
        stack.printItems();
#endif
    }
}

// ? Test Stack push when stack is full
void test_stack_push_full()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    populate_stack(&stack);

    TEST_ASSERT_EQUAL(false, stack.push(SIZE + 1));
}

// ? Test Stack front and back
void test_stack_front_back()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    for (uint8_t i = 1; i < SIZE; i++)
    {
        stack.push(i);

        TEST_ASSERT_EQUAL(i, stack.front());

        TEST_ASSERT_EQUAL(1, stack.back());
    }
}

// ? Test Stack size
void test_stack_size()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    TEST_ASSERT_EQUAL(0, stack.size());
    stack.push(10);
    TEST_ASSERT_EQUAL(1, stack.size());
    stack.push(11);
    TEST_ASSERT_EQUAL(2, stack.size());
    stack.pop();
    TEST_ASSERT_EQUAL(1, stack.size());
    stack.pop();
    TEST_ASSERT_EQUAL(0, stack.size());
    stack.pop();
    TEST_ASSERT_EQUAL(0, stack.size());
}

// ? Test Stack pop normal
void test_stack_pop()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    populate_stack(&stack);

    for (uint8_t i = SIZE; i >= 1; i--)
    {
        TEST_ASSERT_EQUAL(i, stack.pop());

#if VERBOSE
        stack.printItems();
#endif
    }
}

// ? Test Stack pop when stack is empty
void test_stack_pop_empty()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    TEST_ASSERT_EQUAL(0, stack.pop());

    stack.push(1);
    stack.pop();

    TEST_ASSERT_EQUAL(0, stack.pop());

#if VERBOSE
    stack.printItems();
#endif
}

// ? Test Stack pop with no paremeter (first item)
void test_stack_pop_middle()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>();

    populate_stack(&stack); // H: 5 <-- 4 <-- 3 <-- 2 <-- 1 :T

    TEST_ASSERT_EQUAL(3, stack.pop(2)); // H: 5 <-- 4 <-- 2 <-- 1 :T
    TEST_ASSERT_EQUAL(2, stack.pop(2)); // H: 5 <-- 4 <-- 1 :T
    TEST_ASSERT_EQUAL(4, stack.pop(1)); // H: 5 <-- 1 :T

#if VERBOSE
    stack.print();
#endif

    TEST_ASSERT_EQUAL(SIZE, stack.front());
    TEST_ASSERT_EQUAL(1, stack.back());
    TEST_ASSERT_EQUAL(SIZE - 3, stack.size());

    TEST_ASSERT_EQUAL(5, stack.pop());

#if VERBOSE
    stack.print();
#endif
}

// ? Test Stack pop in the middle of stack
void test_stack_pop_end()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>();

    populate_stack(&stack);

    TEST_ASSERT_EQUAL(0, stack.pop(SIZE));

    TEST_ASSERT_EQUAL(1, stack.pop(SIZE - 1));

#if VERBOSE
    stack.print();
#endif
}

// ? Test Stack Node size()
void test_stack_node_size()
{
    DataStructure::Stack<int> s1 = DataStructure::Stack<int>();

#if VERBOSE
    s1.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(int) + sizeof(int), s1.itemSize());

    DataStructure::Stack<uint32_t> s2 = DataStructure::Stack<uint32_t>();

#if VERBOSE
    s2.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(uint32_t) + sizeof(int), s2.itemSize());
}

// ? Test Stack Copy Constructor
void test_stack_copy_constructor()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    populate_stack(&stack);

    DataStructure::Stack<int> stack2 = stack;

#if VERBOSE
    stack2.print();
#endif

    TEST_ASSERT_EQUAL(stack.size(), stack2.size());
    TEST_ASSERT_EQUAL(stack.front(), stack2.front());
    TEST_ASSERT_EQUAL(stack.back(), stack2.back());
};

// ? Test Stack times of function
void test_stack_times()
{
    unsigned long start, end;

    Serial.println("Tessing Stack APIs times...");
    Serial.println("---");

    start = micros();

    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    end = micros();

    Serial.println("Stack Constructor: " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    for (uint16_t i = 1; i <= SIZE; i++)
        stack.push(i);

    end = micros();

    Serial.println("Stack.push(): " + String((end - start) / SIZE) + " microseconds" + "\n---");

    start = micros();

    for (uint16_t i = 1; i <= SIZE; i++)
        stack.pop(i);

    end = micros();

    Serial.println("Stack.pop(): " + String((end - start) / SIZE) + " microseconds" + "\n---");

    start = micros();

    stack.front();

    end = micros();

    Serial.println("Stack.front(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    stack.back();

    end = micros();

    Serial.println("Stack.back(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    stack.size();

    end = micros();

    Serial.println("Stack.size(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    stack.empty();

    end = micros();

    Serial.println("Stack.empty(): " + String(end - start) + " microseconds" + "\n---");

    start = micros();

    stack.full();

    end = micros();

    Serial.println("Stack.full(): " + String(end - start) + " microseconds" + "\n---");

    for (uint16_t i = 1; i <= SIZE; i++)
        stack.push(i);

    start = micros();

    DataStructure::Stack<int> s2 = stack;

    end = micros();

    Serial.println("Stack Copy Constructor: " + String(end - start) + " microseconds" + "\n---");

    Serial.println("Stack Memory Usage: \n---");

    s2.print();
};

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_push_full);

    RUN_TEST(test_stack_front_back);
    RUN_TEST(test_stack_size);

    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_pop_empty);
    RUN_TEST(test_stack_pop_middle);
    RUN_TEST(test_stack_pop_end);

    RUN_TEST(test_stack_node_size);

    RUN_TEST(test_stack_copy_constructor);

    RUN_TEST(test_stack_times);

    UNITY_END(); // End unity testing
}

void loop()
{
}