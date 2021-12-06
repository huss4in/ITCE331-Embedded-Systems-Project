#include <Arduino.h>

#include "Lists.h"
#include "CPU.h"

void setup()
{
    // Begin Serial Communication
    Serial.begin(115200);
}

void loop()
{
    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes;

    // Set sample processes
    processes.push(CPU::Process(0, 4, 2));
    processes.push(CPU::Process(1, 2, 4));
    processes.push(CPU::Process(2, 3, 6));
    processes.push(CPU::Process(3, 5, 10));
    processes.push(CPU::Process(4, 1, 8));
    processes.push(CPU::Process(5, 4, 12));
    processes.push(CPU::Process(6, 6, 7));

    // Print the processes
    processes.print();

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::Fist_Come_First_Served, &processes);

    while (true)
        ;
}
