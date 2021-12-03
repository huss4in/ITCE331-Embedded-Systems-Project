#define SIZE 5

// * Push help function
void populate_queue(DataStructure::Queue<int> *queue)
{
    for (uint8_t i = 1; i <= SIZE; i++)
        queue->push(i);

#if VERBOSE
    queue->print();
#endif
}

// ? Test Queue push normal
void test_queue_push()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        TEST_ASSERT_EQUAL(true, queue.push(i));
#if VERBOSE
        queue.printItems();
#endif
    }
}

// ? Test Queue push when queue is full
void test_queue_push_full()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue);

    TEST_ASSERT_EQUAL(false, queue.push(SIZE + 1));
}

// ? Test Queue pop normal
void test_queue_pop()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue);

    for (uint8_t i = 1; i <= SIZE; i++)
    {
        TEST_ASSERT_EQUAL(i, queue.pop());

#if VERBOSE
        queue.printItems();
#endif
    }
}

// ? Test Queue pop when queue is empty
void test_queue_pop_empty()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    TEST_ASSERT_EQUAL(0, queue.pop());

    queue.push(1);
    queue.pop();

    TEST_ASSERT_EQUAL(0, queue.pop());

#if VERBOSE
    queue.printItems();
#endif
}

// ? Test Queue front and back
void test_queue_front_back()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    for (uint8_t i = 1; i < SIZE; i++)
    {
        queue.push(i);

        TEST_ASSERT_EQUAL(1, queue.front());

        TEST_ASSERT_EQUAL(i, queue.back());
    }
}

// ? Test Queue size
void test_queue_size()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    TEST_ASSERT_EQUAL(0, queue.size());
    queue.push(10);
    TEST_ASSERT_EQUAL(1, queue.size());
    queue.push(11);
    TEST_ASSERT_EQUAL(2, queue.size());
    queue.pop();
    TEST_ASSERT_EQUAL(1, queue.size());
    queue.pop();
    TEST_ASSERT_EQUAL(0, queue.size());
    queue.pop();
    TEST_ASSERT_EQUAL(0, queue.size());
}

// ? Test Queue pop with no paremeter (first item)
void test_queue_pop_index()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>();

    populate_queue(&queue);

    TEST_ASSERT_EQUAL(1, queue.pop_index());

#if VERBOSE
    queue.printItems();
#endif
}

// ? Test Queue pop in the middle of queue
void test_queue_pop_index_middle()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue); // H: 1 <-- 2 <-- 3 <-- 4 <-- 5 :T

    TEST_ASSERT_EQUAL(3, queue.pop_index(2)); // H: 1 <-- 2 <-- 4 <-- 5 :T
    TEST_ASSERT_EQUAL(4, queue.pop_index(2)); // H: 1 <-- 2 <-- 5 :T
    TEST_ASSERT_EQUAL(2, queue.pop_index(1)); // H: 1 <-- 5 :T

    TEST_ASSERT_EQUAL(1, queue.front());
    TEST_ASSERT_EQUAL(5, queue.back());
    TEST_ASSERT_EQUAL(2, queue.size());

#if VERBOSE
    queue.printItems();
#endif
}

// ? Test Queue pop in the middle of queue
void test_queue_pop_index_end()
{
    DataStructure::Queue<int> queue = DataStructure::Queue<int>(SIZE);

    populate_queue(&queue);

    TEST_ASSERT_EQUAL(SIZE, queue.pop_index(SIZE - 1));

#if VERBOSE
    queue.printItems();
#endif
}
