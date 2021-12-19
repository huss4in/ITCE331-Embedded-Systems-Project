uint8_t CPU::Algorithm::ROUND_ROBIN_QUANTUM = 2;
bool CPU::Algorithm::PRIORITY_HIGH = false;

// Fist Come First Served Scheduling Algorithm
void CPU::Algorithm::Fist_Come_First_Served(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int time = 0;

    while (processes->notEmpty())
    {
        CPU::Process process = CPU::Process();

        while (time < processes->front().arrival_time)
            time++, process.temp_burst_time++;

        if (process.temp_burst_time > 0)
        {
            process.id = -1, process.completion_time = time;

            gantt->push(process);
        }

        process = processes->pop();

        process.set_response_time(time);

        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            time++;
        }

        process.set_completion_time(time);

        // Update the Gantt Chart
        gantt->push(process);

        process.temp_burst_time = 0;

        // Update the completion time to the queue
        table->push(process);
    }
}

// Shortest Job First (Non-Preemptive) Scheduling Algorithm
void CPU::Algorithm::Shortest_Job_First(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes->empty())
    {
        while (clock < processes->front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }

        process = CPU::Process::pop_index(processes, CPU::Process::min_BT_index(*processes, clock));
        process.set_response_time(clock);
        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        process.set_completion_time(clock);
        gantt->push(process);
        process.temp_burst_time = 0;
        table->push(process);
    }
}

// Shortest Job First Scheduling Algorithm
void CPU::Algorithm::Shortest_Job_First_Primitive(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes->empty())
    {
        while (clock < processes->front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }

        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }

        process = CPU::Process::pop_index(processes, CPU::Process::min_BT_index(*processes, clock));

        if (process.arrival_time == process.initial_arrival_time)
            process.set_response_time(clock);

        while (process.burst_time_left > 0 && (processes->empty() || clock < processes->front().arrival_time || process.burst_time_left <= CPU::Process::min_BT(*processes, clock)))
        {
            process.burst_time_left--;
            process.temp_burst_time++;
            clock++;
        }

        if (process.burst_time_left == 0)
        {
            process.arrival_time = process.initial_arrival_time;
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;
            table->push(process);
        }
        else
        {
            process.arrival_time = clock;
            process.completion_time = clock;
            gantt->push(process);
            process.temp_burst_time = 0;
            processes->push(process);
        }
    }
}

// Longest Job First (Non-Preemptive) Scheduling Algorithm
void CPU::Algorithm::Longest_Job_First(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;
    CPU::Process process;

    while (!processes->empty())
    {
        while (clock < processes->front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.set_completion_time(clock);
            gantt->push(process);
        }
        process = CPU::Process::pop_index(processes, CPU::Process::max_BT_index(*processes, clock));
        process.set_response_time(clock);
        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        process.set_completion_time(clock);
        gantt->push(process);
        process.temp_burst_time = 0;
        table->push(process);
    }
}

// Longest Job First Scheduling Algorithm
void CPU::Algorithm::Longest_Job_First_Primitive(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes->empty())
    {
        while (clock < processes->front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }
        process = CPU::Process::pop_index(processes, CPU::Process::max_BT_index(*processes, clock));
        if (process.arrival_time == process.initial_arrival_time)
            process.set_response_time(clock);

        while (process.burst_time_left > 0 && (processes->empty() || clock < processes->front().arrival_time || process.burst_time_left >= CPU::Process::max_BT(*processes, clock)))
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        if (process.burst_time_left == 0)
        {
            process.arrival_time = process.initial_arrival_time;
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;
            table->push(process);
        }
        else
        {
            process.arrival_time = clock;
            process.completion_time = clock;
            gantt->push(process);
            process.temp_burst_time = 0;
            processes->push(process);
        }
    }
}

// Round Robin Scheduling Algorithm
void CPU::Algorithm::Round_Robin(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (processes->notEmpty())
    {
        while (clock < processes->front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }
        process = processes->pop();

        if (process.arrival_time == process.initial_arrival_time)
            process.set_response_time(clock);

        while (process.burst_time_left > 0 && (process.temp_burst_time < ROUND_ROBIN_QUANTUM || processes->empty() || clock < processes->front().arrival_time))
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }

        if (process.burst_time_left == 0)
        {
            process.arrival_time = process.initial_arrival_time;
            process.set_completion_time(clock);
            gantt->push(process);

            process.temp_burst_time = 0;
            table->push(process);
        }
        else
        {
            process.arrival_time = clock;
            process.completion_time = clock;
            gantt->push(process);

            process.temp_burst_time = 0;
            processes->push(process);
        }
    }
}

// Priority Non-Preemptive Scheduling Algorithm
void CPU::Algorithm::Priority(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    if (PRIORITY_HIGH == 1)
    {
        while (!processes->empty())
        {
            while (clock < processes->front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(processes, CPU::Process::max_priority_index(*processes, clock, PRIORITY_HIGH));
            process.set_response_time(clock);

            while (process.burst_time_left > 0)
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;

            table->push(process);
        }
    }
    else
    {
        while (!processes->empty())
        {
            while (clock < processes->front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(processes, CPU::Process::max_priority_index(*processes, clock, PRIORITY_HIGH));
            process.set_response_time(clock);

            while (process.burst_time_left > 0)
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;

            table->push(process);
        }
    }
}

// Priority Preemptive Scheduling Algorithm
void CPU::Algorithm::Priority_Primitive(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    if (PRIORITY_HIGH == 1)
    {
        while (!processes->empty())
        {
            while (clock < processes->front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(processes, CPU::Process::max_priority_index(*processes, clock, PRIORITY_HIGH));
            if (process.arrival_time == process.initial_arrival_time)
                process.set_response_time(clock);
            while (process.burst_time_left > 0 && (processes->empty() || clock < processes->front().arrival_time || process.priority >= CPU::Process::max_priority(*processes, clock, PRIORITY_HIGH)))
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            if (process.burst_time_left == 0)
            {
                process.arrival_time = process.initial_arrival_time;
                process.set_completion_time(clock);
                gantt->push(process);
                process.temp_burst_time = 0;
                table->push(process);
            }
            else
            {
                process.arrival_time = clock;
                process.completion_time = clock;
                gantt->push(process);
                process.temp_burst_time = 0;
                processes->push(process);
            }
        }
    }
    else
    {
        while (!processes->empty())
        {
            while (clock < processes->front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(processes, CPU::Process::max_priority_index(*processes, clock, PRIORITY_HIGH));

            if (process.arrival_time == process.initial_arrival_time)
                process.set_response_time(clock);

            while (process.burst_time_left > 0 && (processes->empty() || clock < processes->front().arrival_time || process.priority <= CPU::Process::max_priority(*processes, clock, PRIORITY_HIGH)))
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            if (process.burst_time_left == 0)
            {
                process.arrival_time = process.initial_arrival_time;
                process.set_completion_time(clock);
                gantt->push(process);
                process.temp_burst_time = 0;
                table->push(process);
            }
            else
            {
                process.arrival_time = clock;
                process.completion_time = clock;
                gantt->push(process);
                process.temp_burst_time = 0;
                processes->push(process);
            }
        }
    }

    // return table;
}

// Highest Response Ratio Next Scheduling Algorithm
void CPU::Algorithm::Highest_Response_Ratio_Next(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes->empty())
    {
        while (clock < processes->front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }
        process = CPU::Process::pop_index(processes, CPU::Process::max_response_ratio_index(*processes, clock));
        process.set_response_time(clock);

        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        process.set_completion_time(clock);
        gantt->push(process);
        process.temp_burst_time = 0;

        table->push(process);
    }
}
