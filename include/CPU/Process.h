uint8_t CPU::Process::nextID = 0;

// Reset the process ID counter
void CPU::Process::resetID()
{
    nextID = 0;
}

// Constructor
CPU::Process::Process(int arrival_time, int burst_time, int priority = 0)
{
    this->id = ++nextID;
    this->arrival_time = arrival_time;
    this->burst_time = burst_time;
    this->priority = priority;

    this->initial_arrival_time = this->arrival_time;
    this->burst_time_left = this->burst_time;
}

// Default constructor
CPU::Process::Process()
{
    this->id = 0;
    this->arrival_time = 0;
    this->burst_time = 0;
    this->priority = 0;

    this->initial_arrival_time = this->arrival_time;
    this->burst_time_left = this->burst_time;
}

bool CPU::Process::operator<(const CPU::Process &other) const
{
    return this->arrival_time > other.arrival_time;
}

bool CPU::Process::operator>(const CPU::Process &other) const
{
    return this->arrival_time < other.arrival_time;
}

// Print process
size_t CPU::Process::printTo(Print &printer) const
{
    size_t size = 0;

    size += printer.print("<");
    size += printer.print(this->id);
    size += printer.print("|");
    size += printer.print(this->arrival_time);
    size += printer.print("|");
    size += printer.print(this->burst_time);
    size += printer.print("|");
    size += printer.print(this->priority);
    size += printer.print("|");
    size += printer.print(this->completion_time);
    size += printer.print("|");
    size += printer.print(this->turnaround_time);
    size += printer.print("|");
    size += printer.print(this->response_time);
    size += printer.print("|");
    size += printer.print(this->waiting_time);
    size += printer.print(">");

    return size;
}

// Set completion time
void CPU::Process::set_completion_time(int time)
{
    completion_time = time;
    turnaround_time = completion_time - initial_arrival_time;
    waiting_time = turnaround_time - burst_time;
}

// Set response time
void CPU::Process::set_response_time(int time)
{
    response_time = time - initial_arrival_time;
}

CPU::Process CPU::Process::pop_index(DataStructure::Queue<CPU::Process> *processes, int index)
{

    if (index == 0)
        return processes->pop();

    CPU::Process process;

    DataStructure::Queue<CPU::Process> temp;

    for (int i = 0; i < index; i++)
        temp.push(processes->pop());

    process = processes->pop();

    while (!processes->empty())
        temp.push(processes->pop());

    (*processes) = temp;

    return process;
}

int CPU::Process::min_BT(DataStructure::Queue<CPU::Process> main_queue, int clock)
{
    int min = 0;
    while (!main_queue.empty() && main_queue.front().arrival_time <= clock)
    {
        if (min == 0 || min > main_queue.front().burst_time_left)
            min = main_queue.front().burst_time_left;
        main_queue.pop();
    }
    return min;
}

// Function to implement maximum Burst Time
int CPU::Process::max_BT(DataStructure::Queue<CPU::Process> main_queue, int limit)
{
    int max = 0;
    while (!main_queue.empty() && main_queue.front().arrival_time <= limit)
    {
        if (main_queue.front().burst_time_left > max)
            max = main_queue.front().burst_time_left;
        main_queue.pop();
    }
    return max;
}

int CPU::Process::min_BT_index(DataStructure::Queue<CPU::Process> main_queue, int limit)
{
    int index, i = 0;
    int min = 0;

    while (!main_queue.empty() && main_queue.front().arrival_time <= limit)
    {
        if (min == 0 || main_queue.front().burst_time_left < min)
        {
            min = main_queue.front().burst_time_left;
            index = i;
        }
        main_queue.pop();
        i++;
    }
    return index;
}

// Function to find maximum Burst Time Index w.r.t clock limit
int CPU::Process::max_BT_index(DataStructure::Queue<CPU::Process> main_queue, int limit)
{
    int index, i = 0;
    int max = 0;

    while (!main_queue.empty() && main_queue.front().arrival_time <= limit)
    {
        if (main_queue.front().burst_time_left > max)
        {
            max = main_queue.front().burst_time_left;
            index = i;
        }
        main_queue.pop();
        i++;
    }

    return index;
}

// Function to implement maximum priority w.r.t
// priority and also 2nd argument has boolean
// variable because we need to specify
// True=highest number as highest priority
// False=lowest number as highest priority
int CPU::Process::max_priority(DataStructure::Queue<CPU::Process> main_priority_queue, int limit, bool high)
{
    int max = -1;
    if (high == 1)
    {
        while (!main_priority_queue.empty() && main_priority_queue.front().arrival_time <= limit)
        {
            if (main_priority_queue.front().priority > max)
                max = main_priority_queue.front().priority;
            main_priority_queue.pop();
        }
    }
    else
    {
        while (!main_priority_queue.empty() && main_priority_queue.front().arrival_time <= limit)
        {
            if (max == -1 || main_priority_queue.front().priority < max)
                max = main_priority_queue.front().priority;
            main_priority_queue.pop();
        }
    }
    return max;
}

// Function to implement maximum priority index
int CPU::Process::max_priority_index(DataStructure::Queue<CPU::Process> main_queue, int limit, bool high)
{
    int max = -1, i = 0, index = 0;
    if (high == 1)
    {
        while (!main_queue.empty() && main_queue.front().arrival_time <= limit)
        {
            if (main_queue.front().priority > max)
            {
                max = main_queue.front().priority;
                index = i;
            }
            main_queue.pop();
            i++;
        }
    }
    else
    {
        while (!main_queue.empty() && main_queue.front().arrival_time <= limit)
        {
            if (max == -1 || main_queue.front().priority < max)
            {
                max = main_queue.front().priority;
                index = i;
            }
            main_queue.pop();
            i++;
        }
    }
    return index;
}

// Function to implement maximum Response Ratio
// index w.r.t clock limit for arrival time
int CPU::Process::max_response_ratio_index(DataStructure::Queue<CPU::Process> ready_queue, int limit)
{
    int index, i = 0;
    double response_ratio = 0, max = 0;

    while (!ready_queue.empty() && ready_queue.front().arrival_time <= limit)
    {
        response_ratio = ((double)(limit - ready_queue.front().arrival_time) + ready_queue.front().burst_time_left) / ready_queue.front().burst_time_left;
        if (response_ratio > max)
        {
            max = response_ratio;
            index = i;
        }
        i++;
        ready_queue.pop();
    }

    return index;
}