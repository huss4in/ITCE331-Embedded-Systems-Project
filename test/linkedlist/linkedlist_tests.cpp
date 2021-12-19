#include <Arduino.h>
#include <unity.h>

#include "Lists.h"

// #define VERBOSE true

#define SIZE 10

// ? Test LinkedList push normal
void test_linkedlist_push()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        bool result = list.push(i);

#if VERBOSE
        list.printItems();
#endif

        TEST_ASSERT_EQUAL(true, result);
    }
}

// * Populate the list 1 to SIZE
void populate_list(DataStructure::LinkedList<int> *list)
{
    for (uint8_t i = 1; i <= SIZE; i++)
        list->push(i);

#if VERBOSE
    list->print();
#endif
}

// ? Test LinkedList push when list is full
void test_linkedlist_push_full()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

    populate_list(&list);

    bool result = list.push(SIZE + 1);

#if VERBOSE
    list.printItems();
#endif

    TEST_ASSERT_EQUAL(false, result);
}

// ? Test LinkedList front and back
void test_linkedlist_front_back()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        list.push(i);

#if VERBOSE
        list.printItems();
#endif

        TEST_ASSERT_EQUAL(1, list.front());

        TEST_ASSERT_EQUAL(i, list.back());
    }
}

// ? Test LinkedList size
void test_linkedlist_size()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

#if VERBOSE
    list.print();
#endif

    TEST_ASSERT_EQUAL(0, list.size());
    list.push(10);

#if VERBOSE
    list.print();
#endif

    TEST_ASSERT_EQUAL(1, list.size());
    list.push(11);

#if VERBOSE
    list.print();
#endif

    TEST_ASSERT_EQUAL(2, list.size());
    list.pop();

#if VERBOSE
    list.print();
#endif

    TEST_ASSERT_EQUAL(1, list.size());
    list.pop();

#if VERBOSE
    list.print();
#endif

    TEST_ASSERT_EQUAL(0, list.size());
    list.pop();

#if VERBOSE
    list.print();
#endif

    TEST_ASSERT_EQUAL(0, list.size());
}

// ? Test LinkedList pop normal
void test_linkedlist_pop()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

    populate_list(&list);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        int result = list.pop();

#if VERBOSE
        list.printItems();
#endif

        TEST_ASSERT_EQUAL(i, result);

        TEST_ASSERT_EQUAL(SIZE - i, list.size());
    }
}

// ? Test LinkedList pop when list is empty
void test_linkedlist_pop_empty()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

#if VERBOSE
    list.printHeader();
#endif

    int result = list.pop();

#if VERBOSE
    list.printItems();
#endif

    TEST_ASSERT_EQUAL(0, result);

    list.push(1);

#if VERBOSE
    list.printItems();
#endif

    list.pop();

#if VERBOSE
    list.printItems();
#endif

    TEST_ASSERT_EQUAL(0, list.pop());
}

// ? Test LinkedList pop in the middle of list
void test_linkedlist_pop_middle()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

    populate_list(&list); // H: 1 <-- 2 <-- 3 <-- 4 <-- 5 :T

    int result = list.pop(2); // 3

#if VERBOSE
    list.printItems();
#endif

    TEST_ASSERT_EQUAL(3, result); // H: 1 <-- 2 <-- 4 <-- 5 :T

    result = list.pop(2); // 4

#if VERBOSE
    list.printItems();
#endif

    TEST_ASSERT_EQUAL(4, result); // H: 1 <-- 2 <-- 5 :T

    result = list.pop(1); // 2

#if VERBOSE
    list.printItems();
#endif

    TEST_ASSERT_EQUAL(2, result); // H: 1 <-- 5 :T

    TEST_ASSERT_EQUAL(1, list.front());
    TEST_ASSERT_EQUAL(SIZE, list.back());
    TEST_ASSERT_EQUAL(SIZE - 3, list.size());
}

// ? Test LinkedList pop in the middle of list
void test_linkedlist_pop_end()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

    populate_list(&list);

    TEST_ASSERT_EQUAL(SIZE, list.pop(SIZE - 1));

#if VERBOSE
    list.printItems();
#endif
}

// ? Test LinkedList Node size()
void test_linkedlist_node_size()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>();

#if VERBOSE
    list.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(int) + sizeof(int) * 2, list.itemSize());

    DataStructure::LinkedList<uint32_t> list2 = DataStructure::LinkedList<uint32_t>();

#if VERBOSE
    list2.print();
#endif

    TEST_ASSERT_EQUAL(sizeof(uint32_t) + sizeof(int) * 2, list2.itemSize());
}

// ? Test LinkedList Copy Constructor
void test_linkedlist_copy_constructor()
{
    DataStructure::LinkedList<int> list = DataStructure::LinkedList<int>(SIZE);

    populate_list(&list);

    DataStructure::LinkedList<int> list2 = list;

#if VERBOSE
    list2.print();
#endif

    TEST_ASSERT_EQUAL(list.size(), list2.size());
    TEST_ASSERT_EQUAL(list.front(), list2.front());
    TEST_ASSERT_EQUAL(list.back(), list2.back());
};

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    RUN_TEST(test_linkedlist_push);
    RUN_TEST(test_linkedlist_push_full);

    RUN_TEST(test_linkedlist_front_back);
    RUN_TEST(test_linkedlist_size);

    RUN_TEST(test_linkedlist_pop);
    RUN_TEST(test_linkedlist_pop_empty);
    RUN_TEST(test_linkedlist_pop_middle);
    RUN_TEST(test_linkedlist_pop_end);

    RUN_TEST(test_linkedlist_node_size);

    RUN_TEST(test_linkedlist_copy_constructor);

    UNITY_END(); // End unity testing
}

void loop()
{
}
