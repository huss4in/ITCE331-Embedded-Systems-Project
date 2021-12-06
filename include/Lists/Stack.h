
template <typename Data>
DataStructure::Stack<Data>::Stack(uint16_t maxItems, uint16_t maxMemory)
{
    this->count = 0;

    this->head = nullptr;
    this->tail = nullptr;

    this->maxMemory = maxMemory;
    this->maxItems = maxMemory / sizeof(Node);

    if (maxItems > 0 && this->maxItems > maxItems)
        this->maxItems = maxItems;
}

// Destructor
template <typename Data>
DataStructure::Stack<Data>::~Stack()
{
    for (Node *node = this->head; node != nullptr; node = this->head)
    {
        this->head = node->next;
        delete node;
    }
}

// Copy Constructor
template <typename Data>
DataStructure::Stack<Data>::Stack(const Stack &stack)
{
    this->count = 0;

    this->head = nullptr;
    this->tail = nullptr;

    this->maxMemory = stack.maxMemory;
    this->maxItems = stack.maxItems;

    for (Node *node = stack.head; node != nullptr; node = node->next)
        this->push(node->data);
}

// Assignment operator
template <typename Data>
DataStructure::Stack<Data> &DataStructure::Stack<Data>::operator=(const Stack &stack)
{
    this->count = 0;

    this->head = nullptr;
    this->tail = nullptr;

    this->maxMemory = stack.maxMemory;
    this->maxItems = stack.maxItems;

    for (Node *node = stack.head; node != nullptr; node = node->next)
        this->push(node->data);

    return *this;
}

// Push data into the stack
template <typename Data>
bool DataStructure::Stack<Data>::push(Data data)
{
    if (this->full())
        return false;

    Node *node = new Node(data);

    if (node == nullptr)
        return false;

    if (this->empty())
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
        node->next = this->head;
        this->head = node;
    }

    this->count++;

    return true;
}

// Pop data from the stack
template <typename Data>
Data DataStructure::Stack<Data>::pop()
{
    if (this->empty())
        return Data();

    Data data = this->head->data;

    Node *ptr = this->head;

    this->head = this->head->next;

    delete ptr;

    this->count--;

    return data;
}

// Pop and Return data at index
template <typename Data>
Data DataStructure::Stack<Data>::pop_index(uint16_t index)
{
    // H: 5 <-- 4 <-- 3 <-- 2 <-- 1 :T | index = 3

    if (this->empty() || index >= this->size())
        return Data();

    if (index == 0)
        return this->pop();

    Node *ptr = this->head;

    for (uint8_t i = 0; i < index - 1; i++)
        ptr = ptr->next;

    Data data = ptr->next->data;

    Node *to_delete = ptr->next;

    ptr->next = to_delete->next;

    delete to_delete;

    this->count--;

    return data;
}

// Get data in the front of the stack.
template <typename Data>
Data DataStructure::Stack<Data>::front()
{
    if (this->empty())
        return Data();

    return this->head->data;
}

// Get data in the back of the stack.
template <typename Data>
Data DataStructure::Stack<Data>::back()
{
    if (this->empty())
        return Data();

    return this->tail->data;
}

// print stack header
template <typename Data>
void DataStructure::Stack<Data>::printHeader()
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

// print stack items
template <typename Data>
void DataStructure::Stack<Data>::printItems()
{
    Node *ptr = this->head;

    // Serial.print("---\n");
    Serial.print("H: ");
    Serial.print(ptr->data);

    for (uint8_t i = 1; i < this->size(); i++)
    {
        ptr = ptr->next;
        Serial.print(" <-- ");
        Serial.print(ptr->data);
    }

    Serial.print(" :T");
    Serial.print("\n---");

    Serial.println();
}