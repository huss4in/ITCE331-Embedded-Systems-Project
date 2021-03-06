// Constructor
template <typename Data>
DataStructure::DoubleLinkedList<Data>::DoubleLinkedList(uint16_t maxItems, uint16_t maxMemory)
{
    this->count = 0;

    this->head = nullptr, this->tail = nullptr;

    this->maxMemory = maxMemory;
    this->maxItems = maxMemory / sizeof(Node);

    if (this->maxItems > maxItems)
        this->maxItems = maxItems;
}

// Copy Constructor
template <typename Data>
DataStructure::DoubleLinkedList<Data>::DoubleLinkedList(const DoubleLinkedList &list)
{
    // Use the assignment operator
    *this = list;
}

// Assignment operator
template <typename Data>
DataStructure::DoubleLinkedList<Data> &DataStructure::DoubleLinkedList<Data>::operator=(const DoubleLinkedList &list)
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
DataStructure::DoubleLinkedList<Data>::~DoubleLinkedList()
{
    this->tail->next = nullptr;

    for (Node *node = this->head; node != nullptr; node = this->head)
    {
        this->head = node->next;
        delete node;
    }
}

// Push item to the list.
template <typename Data>
bool DataStructure::DoubleLinkedList<Data>::push(Data data)
{
    if (this->full())
        return false;

    Node *node = new Node(data);

    if (this->empty())
        this->head = node;
    else
    {
        this->tail->next = node;
        node->prev = this->tail;
    }

    this->tail = node;

    this->count++;

    return true;
}

// Pop item from the list.
template <typename Data>
Data DataStructure::DoubleLinkedList<Data>::pop(uint16_t index)
{
    if (this->empty() || index >= this->size())
        return Data();

    Node *target = this->head;

    if (index == 0)
    {
        this->head = head->next;

        if (this->head != nullptr)
            this->head->prev = nullptr;
        else
            this->tail = nullptr;
    }
    else
    {
        Node *ptr = this->head;

        for (uint16_t i = 0; i < index - 1; i++)
            ptr = ptr->next;

        target = ptr->next;

        ptr->next = target->next;

        if (target->next != nullptr)
            target->next->prev = ptr;
        else
            this->tail = ptr;
    }

    this->count--;

    Data data = target->data;

    delete target;

    return data;
}

// First item in the list.
template <typename Data>
Data DataStructure::DoubleLinkedList<Data>::front()
{
    if (this->empty())
        return Data();

    return this->head->data;
}

// Last item in the list.
template <typename Data>
Data DataStructure::DoubleLinkedList<Data>::back()
{
    if (this->empty())
        return Data();

    return this->tail->data;
}

// Print list header.
template <typename Data>
void DataStructure::DoubleLinkedList<Data>::printHeader()
{
    Serial.print("DoubleLinkedList: ");

    this->listHeader();
}

// Print list items.
template <typename Data>
void DataStructure::DoubleLinkedList<Data>::printItems()
{
    Serial.print("H: ");

    if (this->empty())
    {
        Serial.print("NULL :T");
    }
    else
    {
        Node *ptr = this->head;

        Serial.print(ptr->data);

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
            Serial.print(" <-> ");
            Serial.print(ptr->data);
        }

        Serial.print(" :H\nT: ");

        ptr = this->tail;

        Serial.print(ptr->data);

        while (ptr->prev != nullptr)
        {
            ptr = ptr->prev;
            Serial.print(" <-> ");
            Serial.print(ptr->data);
        }

        Serial.print(" :H");
    }

    Serial.print("\n---");

    Serial.println();
}
