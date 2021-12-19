// Constructor
template <typename Data>
DataStructure::SingleLinkedList<Data>::SingleLinkedList(uint16_t maxItems, uint16_t maxMemory)
{
    this->count = 0;

    this->head = nullptr, this->tail = nullptr;

    this->maxMemory = maxMemory;
    this->maxItems = maxMemory / sizeof(Node);

    if (maxItems > 0 && this->maxItems > maxItems)
        this->maxItems = maxItems;
}

// Copy Constructor
template <typename Data>
DataStructure::SingleLinkedList<Data>::SingleLinkedList(const SingleLinkedList &list)
{
    // Use the assignment operator
    *this = list;
}

// Assignment operator
template <typename Data>
DataStructure::SingleLinkedList<Data> &DataStructure::SingleLinkedList<Data>::operator=(const SingleLinkedList &list)
{
    this->count = 0;

    this->head = nullptr, this->tail = nullptr;

    this->maxMemory = list.maxMemory;
    this->maxItems = list.maxItems;

    for (Node *node = list.head; node != nullptr; node = node->next)
        this->push(node->data);

    return *this;
}

// Destructor
template <typename Data>
DataStructure::SingleLinkedList<Data>::~SingleLinkedList()
{
    for (Node *node = this->head; node != nullptr; node = this->head)
    {
        this->head = node->next;
        delete node;
    }
}

// Push item to the list.
template <typename Data>
bool DataStructure::SingleLinkedList<Data>::push(Data data)
{
    if (this->full())
        return false;

    Node *node = new Node(data);

    if (this->empty())
        this->head = node;
    else
        this->tail->next = node;

    this->tail = node;

    this->count++;

    return true;
}

// Pop item from the list.
template <typename Data>
Data DataStructure::SingleLinkedList<Data>::pop(uint16_t index)
{
    if (this->empty() || index >= this->size())
        return Data();

    Node *target = this->head;

    this->count--;

    if (index == 0)
    {
        this->head = head->next;

        if (this->empty())
            this->tail = nullptr;
    }
    else // H: 1 -> 2 -> 3 -> 4 :T
    {
        Node *ptr = target;

        for (uint16_t i = 0; i < index - 1; i++)
            ptr = ptr->next;

        target = ptr->next;

        ptr->next = target->next;

        if (target == this->tail)
            this->tail = ptr;
    }

    Data data = target->data;

    delete target;

    return data;
}

// First item in the list.
template <typename Data>
Data DataStructure::SingleLinkedList<Data>::front()
{
    if (this->empty())
        return Data();

    return this->head->data;
}

// Last item in the list.
template <typename Data>
Data DataStructure::SingleLinkedList<Data>::back()
{
    if (this->empty())
        return Data();

    return this->tail->data;
}

// Print list header.
template <typename Data>
void DataStructure::SingleLinkedList<Data>::printHeader()
{
    Serial.print("SingleLinkedList: ");

    this->listHeader();
}

// Print list items.
template <typename Data>
void DataStructure::SingleLinkedList<Data>::printItems()
{
    Node *ptr = this->head;

    Serial.print("H: ");

    if (this->empty())
    {
        Serial.print("NULL");
    }
    else
    {
        Serial.print(ptr->data);

        for (uint8_t i = 1; i < this->size(); i++)
        {
            ptr = ptr->next;
            Serial.print(" --> ");
            Serial.print(ptr->data);
        }
    }

    Serial.print(" :T");
    Serial.print("\n---");

    Serial.println();
}