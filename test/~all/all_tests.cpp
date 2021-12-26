#include <Arduino.h>
#include <unity.h>

#include "DataStructure.h"
#include "CPU.h"

void populate_processes(DataStructure::Queue<CPU::Process> *processes)
{
    CPU::Process::resetID();

    // Set sample processes
    processes->push(CPU::Process(0, 4, 2));
    processes->push(CPU::Process(1, 2, 4));
    processes->push(CPU::Process(2, 3, 6));
    processes->push(CPU::Process(3, 5, 10));
    processes->push(CPU::Process(4, 1, 8));
    processes->push(CPU::Process(5, 4, 12));
    processes->push(CPU::Process(6, 6, 7));

    processes->print();
}

DataStructure::Queue<CPU::Process> sample_processes()
{
    DataStructure::Queue<CPU::Process> processes;

    populate_processes(&processes);

    return processes;
}

// ? Test First Come First Served
void Test_First_Come_First_Served()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Fist_Come_First_Served, &processes);
}

// ? Test Shortest Job First
void Test_Shortest_Job_First()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Shortest_Job_First, &processes);
}

// ? Test Shortest Job First Primitive
void Test_Shortest_Job_First_Primitive()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Shortest_Job_First_Primitive, &processes);
}

// ? Test Longest Job First
void Test_Longest_Job_First()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Longest_Job_First, &processes);
}

// ? Test Longest Job First Primitive
void Test_Longest_Job_First_Primitive()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Longest_Job_First_Primitive, &processes);
}

// ? Test Round Robin
void Test_Round_Robin()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Round_Robin, &processes);
}

// ? Test Priority
void Test_Priority()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Priority, &processes);
}

// ? Test Priority Primitive
void Test_Priority_Primitive()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Priority_Primitive, &processes);
}

// ? Test Highest Response Ratio Next
void Test_Highest_Response_Ratio_Next()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes = sample_processes();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Highest_Response_Ratio_Next, &processes);
}

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    RUN_TEST(Test_First_Come_First_Served);
    RUN_TEST(Test_Shortest_Job_First);
    RUN_TEST(Test_Shortest_Job_First_Primitive);
    RUN_TEST(Test_Longest_Job_First);
    RUN_TEST(Test_Longest_Job_First_Primitive);
    RUN_TEST(Test_Round_Robin);
    RUN_TEST(Test_Priority);
    RUN_TEST(Test_Priority_Primitive);
    RUN_TEST(Test_Highest_Response_Ratio_Next);

    UNITY_END(); // End unity testing
}

void loop()
{
}