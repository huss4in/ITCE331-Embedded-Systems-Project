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
    private:
        static uint8_t ROUND_ROBIN_QUANTUM;
        static bool PRIORITY_HIGH;

    public:
        static void Fist_Come_First_Served(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Shortest_Job_First(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Shortest_Job_First_Primitive(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Longest_Job_First(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Longest_Job_First_Primitive(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Round_Robin(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Priority(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Priority_Primitive(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
        static void Highest_Response_Ratio_Next(DataStructure::Queue<CPU::Process> *processes, DataStructure::Queue<CPU::Process> *gantt, DataStructure::Queue<CPU::Process> *table);
    };

    class Display
    {
    public:
        static void repeat(char c, uint16_t num);

        static void printCol(int attr, uint8_t left, uint8_t right);

        static void printLine();

    public:
        static void table(DataStructure::Queue<CPU::Process> *processes);
        static void times(DataStructure::Queue<CPU::Process> *processes);
        static void gantt(DataStructure::Queue<CPU::Process> *gantt);

        static void display(void (*algorithm)(DataStructure::Queue<CPU::Process> *, DataStructure::Queue<CPU::Process> *, DataStructure::Queue<CPU::Process> *), DataStructure::Queue<CPU::Process> *processes);
    };

    static uint16_t countDigit(uint16_t n);
    static void get_times(DataStructure::Queue<CPU::Process> *processes, double *completion_time, double *turnaround_time, double *waiting_time, double *response_time);
};

#include "CPU/Process.h"

#include "CPU/Algorithm.h"

#include "CPU/Display.h"
