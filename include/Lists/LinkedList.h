// print list header.
template <typename Data>
void DataStructure::LinkedList<Data>::printHeader()
{
    Serial.print("LinkedList: ");

    this->listHeader();
}
