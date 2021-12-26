// Push an data into the queue
template <typename Data>
bool DataStructure::Queue<Data>::push(Data data)
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

// print queue header
template <typename Data>
void DataStructure::Queue<Data>::printHeader()
{
    Serial.print("Queue: ");

    this->listHeader();
}