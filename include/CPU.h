class CPU
{
public:
    class Process
    {
    protected:
        static int nextID; // The next ID to assign to a process

    public:
        int id = 0;           // Process ID
        int arrival_time = 0; // Arrival time
        int burst_time = 0;   // Burst Tim
        int priority = 0;     // Priority

        int completion_time = 0; // Completion time
        int turnaround_time = 0; // Turnaround time
        int response_time = 0;   // Response time
        int waiting_time = 0;    // Waiting time

        int initial_arrival_time = 0; // Initial arrival time
        int burst_time_left = 0;      // Burst time left
        int temp_burst_time = 0;      // Temporary burst time

        // Constructor
        Process(int id, int arrival_time, int burst_time, int priority = 0);
        // Default constructor
        Process();

        // Print process
        size_t printTo(Print &printer) const;

        // Set completion time
        void set_completion_time(int time);
        // Set response time
        void set_response_time(int time);

        // Less than operator
        bool operator<(const Process &other) const;
        // Greater than operator
        bool operator>(const Process &other) const;

        static Process pop_index(Lists::Queue<Process> *processes, int index);
        static int min_BT(Lists::Queue<Process> main_queue, int clock);
        static int max_BT(Lists::Queue<Process> main_queue, int limit);
        static int min_BT_index(Lists::Queue<Process> main_queue, int limit);
        static int max_BT_index(Lists::Queue<Process> main_queue, int limit);
        static int max_priority(Lists::Queue<Process> main_priority_queue, int limit, bool high);
        static int max_priority_index(Lists::Queue<Process> main_queue, int limit, bool high);
        static int max_response_ratio_index(Lists::Queue<Process> ready_queue, int limit);
    };

    class Algorithm
    {
    public:
        // Fist Come First Served Scheduling Algorithm
        static void FCFS(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        // Shortest Job First Scheduling Algorithm
        static void SJF_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        // Shortest Job First (Non-Preemptive) Scheduling Algorithm
        static void SJF_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        // Longest Job First Scheduling Algorithm
        static void LJF_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        // Longest Job First (Non-Preemptive) Scheduling Algorithm
        static void LJF_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        // Round Robin Scheduling Algorithm
        static void RR(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        static void RR(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table, int rr_time_slice);
        // Priority Preemptive Scheduling Algorithm
        static void P_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        static void P_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table, bool high);
        // Priority Non-Preemptive Scheduling Algorithm
        static void P_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);
        static void P_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table, bool high);
        // Highest Response Ratio Next Scheduling Algorithm
        static void HRRN(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table);

        // Get total completion time of the processes
        static double get_total_completion_time(Lists::Queue<CPU::Process> processes);
        // Get total waiting time of the processes
        static double get_total_waiting_time(Lists::Queue<CPU::Process> processes);
        // Get total turnaround time of the processes
        static double get_total_turnaround_time(Lists::Queue<CPU::Process> processes);
        // Get total response time of the processes
        static double get_total_reponse_time(Lists::Queue<CPU::Process> processes);
    };

    class Display
    {
    public:
        static void repeat(char c, uint16_t num);

        static void printCol(int attr, uint8_t left, uint8_t right);

        static void printLine(bool p);

    public:
        // return number of digits
        static int countDigit(int n);

        // Function to display Completion Queue and all the time
        static void table(Lists::Queue<CPU::Process> processes);
        // Function to display times
        static void times(Lists::Queue<CPU::Process> processes);
        // Function to display Gantt Chart
        static void gantt(Lists::Queue<CPU::Process> gantt);

        // Preform the Algorithm and display the results
        static void display(void (*algorithm)(Lists::Queue<CPU::Process>, Lists::Queue<CPU::Process> *, Lists::Queue<CPU::Process> *), Lists::Queue<CPU::Process> processes);
    };
};

#include "CPU/Process.h"

#include "CPU/Algorithm.h"

#include "CPU/Display.h"
