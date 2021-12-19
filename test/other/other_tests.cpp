#include <Arduino.h>
#include <unity.h>

template <typename Data>
class Parent
{
public:
    class Node
    {
    public:
        int value;
        Node *next;
    };

    Node *parentNode;

    void setHead(Data data)
    {
        parentNode = new Node();

        parentNode->value = data;
        parentNode->next = nullptr;
    }
};

template <typename Data>
class Child : public Parent<Data>
{
public:
    typename Parent<Data>::Node *childNode;

    void setHead(Data data)
    {
        childNode = new typename Parent<Data>::Node();

        childNode->value = data;
        childNode->next = nullptr;
    }

    void printHeader()
    {
        Serial.print("Child: ");
        Serial.println(childNode->value);
    }
};

// ? Test Queue Node size()
void test()
{
    Child<int> child = Child<int>();

    child.setHead(1);

    child.printHeader();
}

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    RUN_TEST(test);

    UNITY_END(); // End unity testing
}

void loop()
{
}