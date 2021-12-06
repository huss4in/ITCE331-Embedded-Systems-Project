class DataStructure
{
private:
    template <typename Data>
    class List
    {
    public:
        class Node
        {
        public:
            Data data; // Data

            Node(Data data); // Constructor
            ~Node();         // Destructor
        };

    protected:
        uint16_t count;     // Number of elements in the list.
        uint16_t maxItems;  // The maximum number of items the list can hold.
        uint16_t maxMemory; // The maximum memory the list can allocate.

        Node *head, *tail; // The head and tail of the list.

    public:
        bool empty() { return this->count == 0; }             // Returns true if the list is empty, false otherwise.
        bool notEmpty() { return this->count != 0; }          // Returns true if the list is not empty, false otherwise.
        bool full() { return this->count == this->maxItems; } // Returns true if the list is full, false otherwise.

        uint16_t size() { return this->count; }              // Returns the number of items currently in the list.
        uint16_t maxSize() { return this->maxItems; }        // Returns the size of the list (maximum number of items).
        uint16_t maxMemorySize() { return this->maxMemory; } // Returns the size of the list (maximum size in bytes).

        void print() // Print the list.
        {
            this->printHeader();
            this->printItems();
        }

        virtual void printHeader(); // Print list header.
        virtual void printItems();  // Print list items.

        virtual uint16_t itemSize() { return sizeof(*this->head); } // Returns the size of the list item in bytes.
    };

public:
    template <typename Data>
    class Queue : public List<Data>
    {
    public:
        class Node
        {
        public:
            Data data;            // data
            Node *next = nullptr; // next node

            Node(Data data) { this->data = data; } // Constructor
            ~Node() { this->next = nullptr; }      // Destructor
        };

    protected:
        Node *head, *tail; // The head and tail of the queue

    public:
        ~Queue();                                                 // Destructor
        Queue(uint16_t maxItems = -1, uint16_t maxMemory = 1024); // Constructor
        Queue(const Queue &q);                                    // Copy constructor
        Queue &operator=(const Queue &q);                         // Assignment operator

        bool push(Data data);               // Adds item to the queue.
        Data pop();                         // Pop item from the queue.
        Data pop_index(uint16_t index = 0); // Pop item at index.

        Data front(); // First item in the queue.
        Data back();  // Last item in the queue.

        Node *headPtr() { return this->head; } // Return pionter to head.
        Node *tailPtr() { return this->tail; } // Return pionter to tail.

        void printHeader(); // Print queue header.
        void printItems();  // Print queue items.

        uint16_t itemSize() { return sizeof(*this->head); } // Returns the size of the queue item in bytes.
    };

    template <typename Data>
    class Stack : public List<Data>
    {
    public:
        class Node
        {
        public:
            Data data;            // data
            Node *next = nullptr; // next node

            Node(Data data) { this->data = data; } // Constructor
            ~Node() { this->next = nullptr; }      // Destructor
        };

    protected:
        Node *head, *tail; // The head and tail of the stack

    public:
        ~Stack();                                                 // Destructor
        Stack(uint16_t maxItems = -1, uint16_t maxMemory = 1024); // Constructor
        Stack(const Stack &stack);                                // Copy constructor
        Stack &operator=(const Stack &stack);                     // Assignment operator

        bool push(Data data);               // Push item onto the stack
        Data pop();                         // Pop item off the stack
        Data pop_index(uint16_t index = 0); // Pop item at index

        Data front(); // First item in the stack.
        Data back();  // Last item in the stack.

        Node *headPtr() { return this->head; } // Return pionter to head
        Node *tailPtr() { return this->tail; } // Return pionter to tail

        void printHeader(); // Print stack header
        void printItems();  // Print stack items

        uint16_t itemSize() { return sizeof(this->head); } // Returns the size of the stack item in bytes.
    };

    template <typename Data>
    class LinkedList : public List<Data>
    {
    };
};

#include "Lists/Queue.h"

#include "Lists/Stack.h"

#include "Lists/LinkedList.h"
