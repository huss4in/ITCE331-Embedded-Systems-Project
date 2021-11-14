#include <Arduino.h>

#include "Queue.h"
#include "CPU/CPU.h"

void setup()
{
    Serial.begin(9600);

    // Initialize the processes and gantt queue
    Queue<CPU::Process> processes, gantt;

    // Preform the scheduling algorithm
    processes = CPU::Algorithm::Priority_NP(CPU::sample_data(), &gantt);

    // Display scheduled processes
    CPU::Display::table(processes);

    // Display gantt chart
    CPU::Display::gantt_chart(gantt);
}

void loop()
{
}