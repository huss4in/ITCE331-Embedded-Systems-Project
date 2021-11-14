#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(ARDUINO) && ARDUINO < 100
#include "WProgram.h"
#endif

#if __cplusplus <= 199711L
#define nullptr NULL
#endif

template <typename T>
class Queue
{
private:
    class Node
    {
    public:
        T item = T();
        Node *next = nullptr;

        // Constructor
        Node(T item) { this->item = item; }

        // Destructor
        ~Node() { this->next = nullptr; }
    };

    Node *head; // The head of the queue
    Node *tail; // The tail of the queue

    uint16_t count;     // Count in items inside the queue
    uint16_t maxItems;  // The max number of items the queue can hold
    uint16_t maxMemory; // The max memory the queue can hold

public:
    Queue(uint16_t maxItems = -1, uint16_t maxMemory = 2048)
    {
        this->count = 0;

        this->head = nullptr;
        this->tail = nullptr;

        this->maxMemory = maxMemory;
        this->maxItems = maxMemory / sizeof(Node);

        if (maxItems > 0 && this->maxItems > maxItems)
            this->maxItems = maxItems;
    }

    ~Queue()
    {
        for (Node *node = head; node != nullptr; node = head)
        {
            head = node->next;
            delete node;
        }
    }

    // Push an item into the queue
    bool push(T item)
    {
        if (this->full())
            return false;

        Node *node = new Node(item);

        if (node == nullptr)
            return false;

        if (this->empty())
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            this->tail->next = node;
            this->tail = node;
        }

        this->count++;

        return true;
    }

    // Pop them item in the front of the queue
    T pop()
    {
        if (this->empty())
            return T();

        T item = this->head->item;

        Node *ptr = this->head;

        this->head = this->head->next;

        delete ptr;

        this->count--;

        return item;
    }

    // Pop and Peturn item ad index
    T pop_index(uint16_t index = 0)
    {
        if (index < 0 || index >= this->size())
            return T();

        if (index == 0)
            return this->pop();

        Node *ptr = this->head;

        for (uint8_t i = 0; i < index - 1; i++)
            ptr = ptr->next;

        T item = ptr->next->item;

        Node *to_delete = ptr->next;

        ptr->next = to_delete->next;

        delete to_delete;

        this->count--;

        return item;
    }

    // Get the item in the front of the queue.
    T front()
    {
        if (this->empty())
            return T();

        return head->item;
    }

    // Get the item in the back of the queue.
    T back()
    {
        if (this->empty())
            return T();

        return tail->item;
    }

    // Return pointer to head
    T *headPtr()
    {
        if (this->empty())
            return nullptr;

        return &(head->item);
    }

    // Return pointer to tail
    T *tailPtr()
    {
        if (this->empty())
            return nullptr;

        return &(tail->item);
    }

    // Returns the number of items currently in the queue.
    inline uint16_t size() { return this->count; }

    // Returns true if the queue is empty, false otherwise.
    inline bool empty() { return this->count == 0; }

    // Returns true if the queue is not empty, false otherwise.
    inline bool notEmpty() { return this->count != 0; }

    // Returns true if the queue is full, false otherwise.
    inline bool full() { return this->count == this->maxItems; }

    // Returns the size of the queue item in bytes.
    inline uint16_t itemSize() { return sizeof(Node); }

    // Returns the size of the queue (maximum number of items)
    inline uint32_t maxQueueSize() { return this->maxItems; }

    // Returns the size of the queue (maximum size in bytes)
    inline uint16_t maxMemorySize() { return this->maxMemory; }

    // print queue
    void print()
    {
        Serial.print("Queue: ");
        Serial.print(this->size());
        Serial.print(" items * ");
        Serial.print(this->itemSize());
        Serial.print(" bytes / ");
        Serial.print(this->maxMemorySize());
        Serial.print(" max bytes = ");
        Serial.print(this->maxQueueSize());
        Serial.println(" max items");

        Serial.println();
    }

    // print queue
    void printItems()
    {

        Node *ptr = this->head;

        Serial.print("| H: ");
        Serial.print(ptr->item);

        for (uint8_t i = 1; i < this->size(); i++)
        {
            ptr = ptr->next;
            Serial.print(" --> ");
            Serial.print(ptr->item);
        }

        Serial.print(" :T |");

        Serial.print(" Size: ");
        Serial.print(this->size());

        Serial.println();
    }
};
