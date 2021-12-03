class DataStructure
{
private:
    template <typename Data>
    class List
    {
    protected:
        uint16_t count;     // Count in items inside the list
        uint16_t maxItems;  // The max number of items the list can hold
        uint16_t maxMemory; // The max memory the list can allocate

        class Node
        {
        public:
            Data data; // Data

            Node(Data data); // Constructor
            ~Node();         // Destructor
        };

        Node *head, *tail; // The head and tail of the queue

    public:
        // Returns the number of items currently in the queue.
        uint16_t size() { return this->count; }

        // Returns true if the queue is empty, false otherwise.
        bool empty() { return this->count == 0; }

        // Returns true if the queue is not empty, false otherwise.
        bool notEmpty() { return this->count != 0; }

        // Returns true if the queue is full, false otherwise.
        bool full() { return this->count == this->maxItems; }

        // Returns the size of the queue item in bytes.
        uint16_t itemSize() { return sizeof(Node); }

        // Returns the size of the queue (maximum number of items)
        uint16_t maxSize() { return this->maxItems; }

        // Returns the size of the queue (maximum size in bytes)
        uint16_t maxMemorySize() { return this->maxMemory; }
    };

public:
    template <typename Data>
    class Queue : public List<Data>
    {
    private:
        class Node
        {
        public:
            Data data;            // data
            Node *next = nullptr; // next node

            Node(Data data) { this->data = data; } // Constructor
            ~Node() { this->next = nullptr; }      // Destructor
        };

        Node *head, *tail; // The head and tail of the queue

    public:
        // Constructor
        Queue(uint16_t maxItems = -1, uint16_t maxMemory = 2048);

        // Destructor
        ~Queue();

        // Copy Constructor
        Queue(const Queue &q);

        // Assignment operator
        Queue &operator=(const Queue &q);

        // Push an data into the queue
        bool push(Data data);

        // Pop them data in the front of the queue
        Data pop();

        // Pop and Peturn data ad index
        Data pop_index(uint16_t index = 0);

        // Get the data in the front of the queue.
        Data front();

        // Get the data in the back of the queue.
        Data back();

        // Return pointer to head
        Data *headPtr();

        // Return pointer to tail
        Data *tailPtr();

        // print queue
        void print()
        {
            this->printHeader();
            this->printItems();
        }

        // print list header
        void printHeader();

        // print list items
        void printItems();

        // Returns the size of the queue item in bytes.
        uint16_t itemSize() { return sizeof(Node); }
    };

    template <typename Data>
    class Stack : public List<Data>
    {
    private:
        class Node
        {
        public:
            Data data;            // data
            Node *next = nullptr; // next node

            Node(Data data) { this->data = data; } // Constructor
            ~Node() { this->next = nullptr; }      // Destructor
        };

        Node *head, *tail; // The head and tail of the stack

    public:
        // Constructor
        Stack(uint16_t maxItems = -1, uint16_t maxMemory = 2048);

        // Destructor
        ~Stack();

        // Copy Constructor
        Stack(const Stack &stack);

        // Assignment operator
        Stack &operator=(const Stack &stack);

        // Push an data into the stack
        bool push(Data data);

        // Pop them data in the front of the stack
        Data pop();

        // Pop and Peturn data ad index
        Data pop_index(uint16_t index = 0);

        // Get the data in the front of the stack.
        Data front();

        // Get the data in the back of the stack.
        Data back();

        // Return pointer to head
        Data *headPtr();

        // Return pointer to tail
        Data *tailPtr();

        // print queue
        void print()
        {
            this->printHeader();
            this->printItems();
        }

        // print list header
        void printHeader();

        // print list items
        void printItems();

        // Returns the size of the queue item in bytes.
        uint16_t itemSize() { return sizeof(Node); }
    };

    template <typename Data>
    class LinkedList : public List<Data>
    {
    };
};

#include "Lists/Queue.h"

#include "Lists/Stack.h"

#include "Lists/LinkedList.h"
