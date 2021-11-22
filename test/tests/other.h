class P
{
private:
    static int nextID;

public:
    int id;

    P()
    {
        id = ++nextID;
    }

    P(const P &orig)
    {
        id = orig.id;
    }

    P &operator=(const P &orig)
    {
        id = orig.id;
        return (*this);
    }
};

int P::nextID = 0;

void test()
{
    P a;

    Serial.print("a.id = ");
    Serial.println(a.id);

    P b;

    Serial.print("b.id = ");
    Serial.println(b.id);

    P c;

    Serial.print("c.id = ");
    Serial.println(c.id);

    TEST_ASSERT_EQUAL(1, a.id);
    TEST_ASSERT_EQUAL(2, b.id);
    TEST_ASSERT_EQUAL(3, c.id);
}

void test_other()
{
    RUN_TEST(test);
}