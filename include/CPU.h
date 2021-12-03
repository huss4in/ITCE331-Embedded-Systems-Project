class CPU
{
public:
    class Process : public Printable
    {
    protected:
        static uint8_t nextID; // The next ID to assign to a process
    public:
        // Reset Process ID
        static void resetID();

    public:
        uint8_t id = 0;           // Process ID
        uint8_t arrival_time = 0; // Arrival time
        uint8_t burst_time = 0;   // Burst Tim
        uint8_t priority = 0;     // Priority

        uint8_t completion_time = 0; // Completion time
        uint8_t turnaround_time = 0; // Turnaround time
        uint8_t response_time = 0;   // Response time
        uint8_t waiting_time = 0;    // Waiting time

        uint8_t initial_arrival_time = 0; // Initial arrival time
        uint8_t burst_time_left = 0;      // Burst time left
        uint8_t temp_burst_time = 0;      // Temporary burst time

        // Constructor
        Process(int arrival_time, int burst_time, int priority);
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

        static Process pop_index(DataStructure::Queue<Process> *processes, int index);
        static int min_BT(DataStructure::Queue<Process> main_queue, int clock);
        static int max_BT(DataStructure::Queue<Process> main_queue, int limit);
        static int min_BT_index(DataStructure::Queue<Process> main_queue, int limit);
        static int max_BT_index(DataStructure::Queue<Process> main_queue, int limit);
        static int max_priority(DataStructure::Queue<Process> main_priority_queue, int limit, bool high);
        static int max_priority_index(DataStructure::Queue<Process> main_queue, int limit, bool high);
        static int max_response_ratio_index(DataStructure::Queue<Process> ready_queue, int limit);
    };

    class Algorithm
    {
    public:
        // Fist Come First Served Scheduling Algorithm
        static void FCFS(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        // Shortest Job First Scheduling Algorithm
        static void SJF_P(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        // Shortest Job First (Non-Preemptive) Scheduling Algorithm
        static void SJF_NP(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        // Longest Job First Scheduling Algorithm
        static void LJF_P(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        // Longest Job First (Non-Preemptive) Scheduling Algorithm
        static void LJF_NP(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        // Round Robin Scheduling Algorithm
        static void RR(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void RR(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table, int rr_time_slice);
        // Priority Preemptive Scheduling Algorithm
        static void P_P(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void P_P(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table, bool high);
        // Priority Non-Preemptive Scheduling Algorithm
        static void P_NP(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void P_NP(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table, bool high);
        // Highest Response Ratio Next Scheduling Algorithm
        static void HRRN(DataStructure::Queue<CPU::Process> processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);

        // Get total completion time of the processes
        static double get_total_completion_time(DataStructure::Queue<CPU::Process> processes);
        // Get total waiting time of the processes
        static double get_total_waiting_time(DataStructure::Queue<CPU::Process> processes);
        // Get total turnaround time of the processes
        static double get_total_turnaround_time(DataStructure::Queue<CPU::Process> processes);
        // Get total response time of the processes
        static double get_total_reponse_time(DataStructure::Queue<CPU::Process> processes);
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
        static void table(DataStructure::Queue<CPU::Process> processes);
        // Function to display times
        static void times(DataStructure::Queue<CPU::Process> processes);
        // Function to display Gantt Chart
        static void gantt(DataStructure::Queue<CPU::Process> gantt);

        // Preform the Algorithm and display the results
        static void display(void (*algorithm)(DataStructure::Queue<CPU::Process>, DataStructure::Queue<CPU::Process> *, DataStructure::Queue<CPU::Process> *), DataStructure::Queue<CPU::Process> processes);
    };
};

#include "CPU/Process.h"

#include "CPU/Algorithm.h"

#include "CPU/Display.h"
