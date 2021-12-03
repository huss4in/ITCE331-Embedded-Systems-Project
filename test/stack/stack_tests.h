#define SIZE 5

// * Push help function
void push_help(DataStructure::Stack<int> *stack)
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

    push_help(&stack);

    TEST_ASSERT_EQUAL(false, stack.push(SIZE + 1));
}

// ? Test Stack pop normal
void test_stack_pop()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>(SIZE);

    push_help(&stack);

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

// ? Test Stack pop with no paremeter (first item)
void test_stack_pop_index()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>();

    push_help(&stack);

    TEST_ASSERT_EQUAL(5, stack.pop_index());

#if VERBOSE
    stack.print();
#endif
}

// ? Test Stack pop in the middle of stack
void test_stack_pop_index_middle()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>();

    push_help(&stack); // H: 5 <-- 4 <-- 3 <-- 2 <-- 1 :T

    TEST_ASSERT_EQUAL(3, stack.pop_index(2)); // H: 5 <-- 4 <-- 2 <-- 1 :T
    TEST_ASSERT_EQUAL(2, stack.pop_index(2)); // H: 5 <-- 4 <-- 1 :T
    TEST_ASSERT_EQUAL(4, stack.pop_index(1)); // H: 5 <-- 1 :T
    TEST_ASSERT_EQUAL(5, stack.front());
    TEST_ASSERT_EQUAL(1, stack.back());
    TEST_ASSERT_EQUAL(2, stack.size());

#if VERBOSE
    stack.print();
#endif
}

// ? Test Stack pop in the middle of stack
void test_stack_pop_index_end()
{
    DataStructure::Stack<int> stack = DataStructure::Stack<int>();

    push_help(&stack);

    TEST_ASSERT_EQUAL(0, stack.pop_index(SIZE));

    TEST_ASSERT_EQUAL(1, stack.pop_index(SIZE - 1));

#if VERBOSE
    stack.print();
#endif
}