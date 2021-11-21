// ? Test countDigit
void test_countDigit()
{
    TEST_ASSERT_EQUAL(1, CPU::Display::countDigit(1));

    TEST_ASSERT_EQUAL(1, CPU::Display::countDigit(9));

    TEST_ASSERT_EQUAL(5, CPU::Display::countDigit(12345));
}

// ? Test countDigit with zero
void test_countDigit_zero()
{
    TEST_ASSERT_EQUAL(1, CPU::Display::countDigit(0));
}

// ? Test countDigit with negative
void test_countDigit_negative()
{
    TEST_ASSERT_EQUAL(2, CPU::Display::countDigit(-1));

    TEST_ASSERT_EQUAL(4, CPU::Display::countDigit(-101));
}

// ? Test Queue<CPU::Process> Deep Copy
void test_cpu_queue_deep_copy()
{
    Queue<CPU::Process> queue;

    queue.push(CPU::Process(1, 1, 1));
    queue.push(CPU::Process(2, 2, 2));
    queue.push(CPU::Process(3, 3, 3));

    Queue<CPU::Process> second = queue;

    TEST_ASSERT_EQUAL(3, second.size());

    TEST_ASSERT_EQUAL(1, second.front().id);

    TEST_ASSERT_EQUAL(3, second.back().id);
}

void test_cpu()
{
    RUN_TEST(test_countDigit);
    RUN_TEST(test_countDigit_zero);
    RUN_TEST(test_countDigit_negative);
}
