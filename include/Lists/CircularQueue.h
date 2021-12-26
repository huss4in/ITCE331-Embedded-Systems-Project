// Push item the to the circular queue.
template <typename Data>
bool DataStructure::CircularQueue<Data>::push(Data data)
{
    Node *node = new Node(data);

    // H: 1 --> 2 --> 3 --> 4 --> 5 :T -<1

    if (this->empty())
    {
        this->head = node;

        this->count++;
    }
    else if (this->full())
    {
        this->tail->next = node;

        node->next = this->head->next;

        delete this->head;

        this->head = node->next;
    }
    else
    {
        this->tail->next = node;

        this->count++;

        if (this->size() == this->maxItemsCount())
            node->next = this->head;
    }

    this->tail = node;

    return true;
}

// Pop item from the circular queue.
template <typename Data>
Data DataStructure::CircularQueue<Data>::pop(uint16_t index)
{
    if (this->empty())
        return Data();

    // H: 1 --> 2 --> 3 --> 4 --> 5 :T
    //                      ^     ^
    //                      3     t

    this->tail->next = nullptr;

    Node *target = this->head;

    if (index == 0)
        if (this->size() == 1)
            this->head = nullptr, this->tail = nullptr;
        else
            this->head = target->next, this->tail->next = this->head;
    else
    {
        Node *ptr = target;

        for (uint16_t i = 0; i < index - 1; i++)
            ptr = ptr->next;

        target = ptr->next;

        ptr->next = target->next;

        if (target == this->tail)
            this->tail = ptr;
    }

    this->count--;

    Data data = target->data;

    delete target;

    return data;
}

// print queue header
template <typename Data>
void DataStructure::CircularQueue<Data>::printHeader()
{
    Serial.print("CircularQueue: ");

    this->listHeader();
}