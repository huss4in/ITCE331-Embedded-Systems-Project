class Process : public Printable
{
private:
public:
    int id = 0;           // Process ID
    int arrival_time = 0; // Arrival time
    int burst_time = 0;   // Burst Tim
    int priority = 0;     // Priority

    int completion_time = 0; // Completion time
    int turnaround_time = 0; // Turnaround time
    int response_time = 0;   // Response time
    int waiting_time = 0;    // Waiting time

    int initial_arrival_time = 0;
    int burst_time_left = 0;
    int temp_burst_time = 0;

    // Constructor
    Process(int id, int arrival_time, int burst_time, int priority = 0)
    {
        this->id = id;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->priority = priority;

        this->initial_arrival_time = arrival_time;
        this->burst_time_left = burst_time;
    }

    // Default constructor
    Process() { Process(0, 0, 0); }

    size_t printTo(Print &p) const
    {
        size_t size = 0;

        size += p.print("<");
        size += p.print(this->id);
        size += p.print("|");
        size += p.print(this->arrival_time);
        size += p.print("|");
        size += p.print(this->burst_time);
        size += p.print("|");
        size += p.print(this->priority);
        size += p.print("|");
        size += p.print(this->completion_time);
        size += p.print("|");
        size += p.print(this->turnaround_time);
        size += p.print("|");
        size += p.print(this->response_time);
        size += p.print("|");
        size += p.print(this->waiting_time);
        size += p.print(">");

        return size;
    }

    // Set completion time
    void set_completion_time(int time)
    {
        completion_time = time;
        turnaround_time = completion_time - initial_arrival_time;
        waiting_time = turnaround_time - burst_time;
    }

    // Set response time
    void set_response_time(int time)
    {
        response_time = time - initial_arrival_time;
    }

    friend bool operator<(const Process &p1, const Process &p2)
    {
        return p1.arrival_time > p2.arrival_time;
    }

    friend bool operator>(const Process &p1, const Process &p2)
    {
        return p1.arrival_time < p2.arrival_time;
    }

    static Process pop_index(List::Queue<Process> *processes, int index)
    {

        if (index == 0)
            return processes->pop();

        Process process;

        List::Queue<Process> temp;

        for (int i = 0; i < index; i++)
            temp.push(processes->pop());

        process = processes->pop();

        while (!processes->empty())
            temp.push(processes->pop());

        (*processes) = temp;

        return process;
    }

    static int min_BT(List::Queue<Process> main_queue, int clock)
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
    static int max_BT(List::Queue<Process> main_queue, int limit)
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

    static int min_BT_index(List::Queue<Process> main_queue, int limit)
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
    static int max_BT_index(List::Queue<Process> main_queue, int limit)
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
    //priority and also 2nd argument has boolean
    //variable because we need to specify
    // True=highest number as highest priority
    // False=lowest number as highest priority
    static int max_priority(List::Queue<Process> main_priority_queue, int limit, bool high)
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
    static int max_priority_index(List::Queue<Process> main_queue, int limit, bool high)
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
    static int max_response_ratio_index(List::Queue<Process> ready_queue, int limit)
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
};
