#include <Arduino.h>

#include "Queue.h"
#include "CPU/CPU.h"

void setup()
{
    // Begin Serial Communication
    Serial.begin(115200);

    // Initialize the processes and gantt queue
    Queue<CPU::Process> processes, gantt, table;

    // Set sample processes
    processes.push(CPU::Process(1, 0, 5, 3));
    processes.push(CPU::Process(2, 3, 10, 4));
    processes.push(CPU::Process(3, 7, 5, 2));
    processes.push(CPU::Process(4, 8, 2, 5));
    processes.push(CPU::Process(5, 9, 4, 1));

    // Preform the scheduling algorithm
    CPU::Algorithm::FCFS(processes, &gantt, &table);

    // Display gantt chart
    CPU::Display::gantt(gantt);

    // Display scheduled processes
    CPU::Display::table(table);

    // Display the times
    CPU::Display::times(table);
}

void loop()
{
}
