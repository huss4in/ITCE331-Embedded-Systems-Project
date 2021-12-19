class DataStructure
{
private:
    template <typename Data>
    class List
    {
    protected:
        uint16_t count;     // Number of elements in the list.
        uint16_t maxItems;  // The maximum number of items the list can hold.
        uint16_t maxMemory; // The maximum memory the list can allocate.

        class Node
        {
        public:
            Data data; // Data

            Node(Data data) { this->data = data; } // Constructor
        };

        void listHeader()
        {
            Serial.print(this->itemSize());
            Serial.print(" bytes / ");

            Serial.print(this->maxMemorySize());
            Serial.print(" max bytes = ");

            Serial.print(this->maxItemsCount());
            Serial.print(" max items ");

            Serial.print("| Size ");
            Serial.print(this->size());

            Serial.println("\n---");
        }

    public:
        virtual bool empty() { return this->count == 0; }             // Return true if the list is empty.
        virtual bool notEmpty() { return !this->empty(); }            // Return true if the list is not empty.
        virtual bool full() { return this->count == this->maxItems; } // Return true if the list is full.

        virtual uint16_t size() { return this->count; }              // Return the number of items in the list.
        virtual uint16_t maxItemsCount() { return this->maxItems; }  // Return the maximum number of items the list can hold.
        virtual uint16_t maxMemorySize() { return this->maxMemory; } // Return the maximum memory the list can allocate.

        virtual uint16_t itemSize(); // Returns the size of the list item in bytes.

        virtual bool push(Data data);         // Push item to the list.
        virtual Data pop(uint16_t index = 0); // Pop item from the list.

        virtual Data front(); // First item in the list.
        virtual Data back();  // Last item in the list.

        void print() // Print the list.
        {
            this->printHeader();
            this->printItems();
        }

        virtual void printItems();  // Print list items.
        virtual void printHeader(); // Print list header.
    };

    template <typename Data>
    class SingleLinkedList : public List<Data>
    {
    public:
        class Node : public List<Data>::Node
        {
        public:
            Node *next; // Next node.

            Node(Data data) : List<Data>::Node(data) { this->next = nullptr; } // Constructor.
            ~Node() { this->next = nullptr; }                                  // Destructor.
        };

        Node *head, *tail; // Pointer to the head and tail of the list.

    public:
        uint16_t itemSize() { return sizeof(Node); } // Returns the size of the list item in bytes.

        SingleLinkedList(uint16_t maxItems = -1, uint16_t maxMemory = 1024); // Constructor
        SingleLinkedList(const SingleLinkedList &list);                      // Copy constructor
        ~SingleLinkedList();                                                 // Destructor

        Data front(); // First item in the list.
        Data back();  // Last item in the list.

        virtual bool push(Data data);         // Push item to the list.
        virtual Data pop(uint16_t index = 0); // Pop item from the list.

        virtual void printHeader(); // Print list header.
        virtual void printItems();  // Print list items.
    };

    template <typename Data>
    class DoubleLinkedList : public List<Data>
    {
    public:
        class Node : public List<Data>::Node
        {
        public:
            Node *next, *prev; // Next and Previous nodes.

            Node(Data data) : List<Data>::Node(data) { this->next = nullptr, this->prev = nullptr; } // Constructor.
            ~Node() { this->next = nullptr, this->prev = nullptr; }                                  // Destructor.
        };

        Node *head, *tail; // Pointer to the head and tail of the list.

    public:
        uint16_t itemSize() { return sizeof(Node); } // Returns the size of the list item in bytes.

        DoubleLinkedList(uint16_t maxItems = -1, uint16_t maxMemory = 1024); // Constructor
        DoubleLinkedList(const DoubleLinkedList &list);                      // Copy constructor
        ~DoubleLinkedList();                                                 // Destructor

        Data front(); // First item in the list.
        Data back();  // Last item in the list.

        virtual bool push(Data data);         // Push item to the list.
        virtual Data pop(uint16_t index = 0); // Pop item from the list.

        virtual void printHeader(); // Print list header.
        virtual void printItems();  // Print list items.
    };

public:
    template <typename Data>
    class Queue : public SingleLinkedList<Data>
    {
    public:
        Queue(uint16_t maxItems = -1, uint16_t maxMemory = 1024) : SingleLinkedList<Data>(maxItems, maxMemory) {} // Inherit constructor.
        Queue(const Queue &queue) : SingleLinkedList<Data>(queue) {}                                              // Inherit copy constructor.

        bool push(Data data); // Push item to the queue.

        void printHeader(); // Print list header.
    };

    template <typename Data>
    class Stack : public SingleLinkedList<Data>
    {
    public:
        Stack(uint16_t maxItems = -1, uint16_t maxMemory = 1024) : SingleLinkedList<Data>(maxItems, maxMemory) {} // Inherit constructor.
        Stack(const Stack &stack) : SingleLinkedList<Data>(stack) {}                                              // Inherit copy constructor.

        bool push(Data data); // Push item to the stack.

        void printHeader(); // Print list header.
    };

    template <typename Data>
    class LinkedList : public DoubleLinkedList<Data>
    {
    public:
        LinkedList(uint16_t maxItems = -1, uint16_t maxMemory = 1024) : DoubleLinkedList<Data>(maxItems, maxMemory) {} // Inherit constructor.
        LinkedList(const LinkedList &list) : DoubleLinkedList<Data>(list) {}                                           // Inherit copy constructor.

        // bool push(Data data);         // Push item to the list.
        // Data pop(uint16_t index = 0); // Pop item from the list.

        void printHeader(); // Print list header.
    };
};

#include "Lists/SingleLinkedList.h"
#include "Lists/DoubleLinkedList.h"
#include "Lists/LinkedList.h"
#include "Lists/Queue.h"
#include "Lists/Stack.h"
