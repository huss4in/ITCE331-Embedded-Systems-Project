template <typename Data>
DataStructure::Queue<Data>::Queue(uint16_t maxItems, uint16_t maxMemory)
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
DataStructure::Queue<Data>::~Queue()
{
    for (Node *node = this->head; node != nullptr; node = this->head)
    {
        this->head = node->next;
        delete node;
    }
}

// Copy Constructor
template <typename Data>
DataStructure::Queue<Data>::Queue(const Queue &queue)
{
    this->count = 0;

    this->head = nullptr;
    this->tail = nullptr;

    this->maxMemory = queue.maxMemory;
    this->maxItems = queue.maxItems;

    for (Node *node = queue.head; node != nullptr; node = node->next)
        this->push(node->data);
}

// Assignment operator
template <typename Data>
DataStructure::Queue<Data> &DataStructure::Queue<Data>::operator=(const Queue &queue)
{
    this->count = 0;

    this->head = nullptr;
    this->tail = nullptr;

    this->maxMemory = queue.maxMemory;
    this->maxItems = queue.maxItems;

    for (Node *node = queue.head; node != nullptr; node = node->next)
        this->push(node->data);

    return *this;
}

// Push an data into the queue
template <typename Data>
bool DataStructure::Queue<Data>::push(Data data)
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
        this->tail->next = node;
        this->tail = node;
    }

    this->count++;

    return true;
}

// Pop them data in the front of the queue
template <typename Data>
Data DataStructure::Queue<Data>::pop()
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
Data DataStructure::Queue<Data>::pop_index(uint16_t index)
{
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

// Get the data in the front of the queue.
template <typename Data>
Data DataStructure::Queue<Data>::front()
{
    if (this->empty())
        return Data();

    return this->head->data;
}

// Get the data in the back of the queue.
template <typename Data>
Data DataStructure::Queue<Data>::back()
{
    if (this->empty())
        return Data();

    return this->tail->data;
}

// print queue header
template <typename Data>
void DataStructure::Queue<Data>::printHeader()
{
    Serial.print("Queue: ");

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

// print queue items
template <typename Data>
void DataStructure::Queue<Data>::printItems()
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
