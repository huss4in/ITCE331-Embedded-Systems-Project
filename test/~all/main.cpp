#include <Arduino.h>
#include <unity.h>

#include "Lists.h"
#include "CPU.h"

// ? Test fcfs
void test_fcfs()
{
    CPU::Process::resetID();

    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes;

    // Set sample processes
    processes.push(CPU::Process(0, 5, 3));
    processes.push(CPU::Process(3, 10, 4));
    processes.push(CPU::Process(7, 5, 2));
    processes.push(CPU::Process(8, 2, 5));
    processes.push(CPU::Process(9, 4, 1));
    processes.push(CPU::Process(9, 4, 1));

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::FCFS, processes);
}

// ? Test p
void test_p()
{
    CPU::Process::resetID();

    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes;

    // Set sample processes
    processes.push(CPU::Process(0, 5, 3));
    processes.push(CPU::Process(3, 10, 4));
    processes.push(CPU::Process(7, 5, 2));
    processes.push(CPU::Process(8, 2, 5));
    processes.push(CPU::Process(9, 4, 1));
    processes.push(CPU::Process(9, 4, 1));

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::P_P, processes);
}

void setup()
{
    UNITY_BEGIN(); // Begin unity testing

    RUN_TEST(test_fcfs);
    RUN_TEST(test_p);

    UNITY_END(); // End unity testing
}

void loop()
{
}