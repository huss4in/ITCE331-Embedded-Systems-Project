// Push data into the stack
template <typename Data>
bool DataStructure::Stack<Data>::push(Data data)
{
    if (this->full())
        return false;

    Node *node = new Node(data);

    if (this->empty())
        this->head = node, this->tail = node;
    else
        node->next = this->head, this->head = node;

    this->count++;

    return true;
}

// print stack header
template <typename Data>
void DataStructure::Stack<Data>::printHeader()
{
    Serial.print("Stack: ");

    this->listHeader();
}