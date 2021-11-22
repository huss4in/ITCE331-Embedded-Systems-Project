template <typename T>
class Stack
{
private:
    class Node
    {
    public:
        T item;
        Node *next = nullptr;

        // Constructor
        Node(T item) { this->item = item; }

        // Destructor
        ~Node() { this->next = nullptr; }

        // Copy Constructor
        Node(const Node &other) { this->item = other.item, this->next = other.next; }

        // Copy Assignment Operator
        Node &operator=(const Node &other)
        {
            this->item = other.item;
            this->next = other.next;
            return *this;
        }
    };

    Node *head; // The head of the Stack
    Node *tail; // The tail of the Stack

    uint16_t count;     // Count in items inside the Stack
    uint16_t maxItems;  // The max number of items the Stack can hold
    uint16_t maxMemory; // The max memory the Stack can hold

public:
    Stack(uint16_t maxItems = -1, uint16_t maxMemory = 2048)
    {
        this->count = 0;

        this->head = nullptr;
        this->tail = nullptr;

        this->maxMemory = maxMemory;
        this->maxItems = maxMemory / sizeof(Node);

        if (maxItems > 0 && this->maxItems > maxItems)
            this->maxItems = maxItems;
    }

    ~Stack()
    {
        for (Node *node = head; node != nullptr; node = head)
        {
            head = node->next;
            delete node;
        }
    }

    // Copy Constructor
    Stack(const Stack &q)
    {
        this->count = 0;

        this->head = nullptr;
        this->tail = nullptr;

        this->maxMemory = q.maxMemory;
        this->maxItems = q.maxItems;

        for (Node *node = q.head; node != nullptr; node = node->next)
            this->push(node->item);
    }

    // Assignment operator
    Stack &operator=(const Stack &q)
    {
        this->count = 0;

        this->head = nullptr;
        this->tail = nullptr;

        this->maxMemory = q.maxMemory;
        this->maxItems = q.maxItems;

        for (Node *node = q.head; node != nullptr; node = node->next)
            this->push(node->item);

        return *this;
    }

    // Push an item into the Stack
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

    // Pop them item in the front of the Stack
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

    // Get the item in the front of the Stack.
    T front()
    {
        if (this->empty())
            return T();

        return head->item;
    }

    // Get the item in the back of the Stack.
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

    // Returns the number of items currently in the Stack.
    uint16_t size() { return this->count; }

    // Returns true if the Stack is empty, false otherwise.
    bool empty() { return this->count == 0; }

    // Returns true if the Stack is not empty, false otherwise.
    bool notEmpty() { return this->count != 0; }

    // Returns true if the Stack is full, false otherwise.
    bool full() { return this->count == this->maxItems; }

    // Returns the size of the Stack item in bytes.
    uint16_t itemSize() { return sizeof(Node); }

    // Returns the size of the Stack (maximum number of items)
    uint16_t maxSize() { return this->maxItems; }

    // Returns the size of the Stack (maximum size in bytes)
    uint16_t maxMemorySize() { return this->maxMemory; }

    // print Stack
    void print()
    {
        this->printHeader();
        this->printItems();
    }

    // print list header
    void printHeader()
    {
        Serial.print("Stack: ");

        Serial.print(this->itemSize());
        Serial.print(" bytes / ");

        Serial.print(this->maxMemorySize());
        Serial.print(" max bytes = ");

        Serial.print(this->maxSize());
        Serial.print(" max items ");

        Serial.print("| Size ");
        Serial.print(this->size());

        Serial.println();
    }

    // print Stack items
    void printItems()
    {
        Node *ptr = this->head;

        Serial.print("---\n");
        Serial.print("H: ");
        Serial.print(ptr->item);

        for (uint8_t i = 1; i < this->size(); i++)
        {
            ptr = ptr->next;
            Serial.print(" <-- ");
            Serial.print(ptr->item);
        }

        Serial.print(" :T");
        Serial.print("\n---");

        Serial.println();
    }
};
