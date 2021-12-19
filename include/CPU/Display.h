void CPU::Display::repeat(char c, uint16_t num)
{
     for (uint8_t i = 0; i < num; i++)
          Serial.print(c);
}

void CPU::Display::printCol(int attr, uint8_t left, uint8_t right)
{
     uint8_t temp = countDigit(attr);

     left = left - temp / 2 - temp % 2;
     right = right - temp / 2;

     repeat(' ', right);

     Serial.print(attr);

     repeat(' ', left);

     Serial.print("|");
}

void CPU::Display::printLine()
{
     Serial.println("+------------+--------------+------------+----------+-----------------+-----------------+--------------+---------------+");
}

// return number of digits
uint16_t CPU::countDigit(uint16_t n)
{
     uint16_t count = 0;

     if (n <= 0)
          n = -n, count++;

     while (n > 0)
          n = n / 10, count++;

     return count;
}

// Get total times of the processes
void CPU::get_times(DataStructure::Queue<CPU::Process> *processes, double *completion_time, double *waiting_time, double *turnaround_time, double *response_time)
{
     *completion_time = 0;
     *turnaround_time = 0;
     *waiting_time = 0;
     *response_time = 0;

     CPU::Process process;

     for (uint16_t i = 0; i < processes->size(); i++)
     {
          process = processes->pop();

          *completion_time += process.completion_time;
          *turnaround_time += process.turnaround_time;
          *waiting_time += process.waiting_time;
          *response_time += process.response_time;

          processes->push(process);
     }
}

// Function to display Completion Queue and all the time
void CPU::Display::table(DataStructure::Queue<CPU::Process> *processes)
{
     printLine();
     Serial.println("| Process ID | Arrival Time | Burst Time | Priority | Completion Time | Turnaround Time | Waiting Time | Response Time |");
     printLine();

     for (uint16_t i = 0; i < processes->size(); i++)
     {
          Serial.print("|");

          CPU::Process process = processes->pop();

          printCol(process.id, 6, 6);
          printCol(process.initial_arrival_time, 7, 7);
          printCol(process.burst_time, 6, 6);
          printCol(process.priority, 5, 5);
          printCol(process.completion_time, 9, 8);
          printCol(process.turnaround_time, 9, 8);
          printCol(process.waiting_time, 7, 7);
          printCol(process.response_time, 8, 7);

          processes->push(process);

          Serial.println();
     }

     printLine();

     Serial.println("\n");
}

void CPU::Display::times(DataStructure::Queue<CPU::Process> *processes)
{
     uint16_t size = processes->size();

     double completion_time = 0;
     double turnaround_time = 0;
     double waiting_time = 0;
     double response_time = 0;

     CPU::get_times(processes, &completion_time, &turnaround_time, &waiting_time, &response_time);

     Serial.print("\nTotal Completion Time: ");
     Serial.println(completion_time);
     Serial.print("Average Completion Time: ");
     Serial.println(completion_time / size);
     Serial.println();

     Serial.print("\nTotal Turnaround Time: ");
     Serial.println(waiting_time);
     Serial.print("Average Turnaround Time: ");
     Serial.println(waiting_time / size);
     Serial.println();

     Serial.print("\nTotal Waiting Time: ");
     Serial.println(waiting_time);
     Serial.print("Average Waiting Time: ");
     Serial.println(waiting_time / size);
     Serial.println();

     Serial.print("\nTotal Response Time: ");
     Serial.println(response_time);
     Serial.print("Average Response Time: ");
     Serial.println(response_time / size);
     Serial.println();
}

// Function to display Gantt Chart
void CPU::Display::gantt(DataStructure::Queue<CPU::Process> *gantt)
{
     Serial.print("\n+");

     // For 1st row of gantt chart
     for (uint16_t i = 0; i < gantt->size(); i++)
     {
          CPU::Process process = gantt->pop();

          repeat('-', countDigit(process.id) + (process.id != -1) + 2 * process.temp_burst_time);

          Serial.print("+");

          gantt->push(process);
     }

     Serial.print("\n|");

     // For process no. in 2nd row
     for (uint16_t i = 0; i < gantt->size(); i++)
     {
          CPU::Process process = gantt->pop();

          repeat(' ', process.temp_burst_time);

          if (process.id == -1)
               Serial.print("IS");
          else
          {
               Serial.print("P");
               Serial.print(process.id);
          }

          repeat(' ', process.temp_burst_time);

          Serial.print("|");

          gantt->push(process);
     }

     Serial.print("\n+");

     for (uint16_t i = 0; i < gantt->size(); i++)
     {
          CPU::Process process = gantt->pop();

          repeat('-', countDigit(process.id) + (process.id != -1) + 2 * process.temp_burst_time);

          Serial.print("+");

          gantt->push(process);
     }

     Serial.print("\n0");

     int temp, prev = 0;

     // For 3rd row of gantt chart
     for (uint16_t i = 0; i < gantt->size(); i++)
     {
          CPU::Process process = gantt->pop();

          temp = countDigit(process.completion_time);

          repeat(' ', countDigit(process.id) + (process.id != -1) + 2 * process.temp_burst_time - temp / 2 - prev);

          Serial.print(process.completion_time);

          prev = temp / 2 - temp % 2 == 0;

          gantt->push(process);
     }

     Serial.print("\n\n");
}

// Preform the Algorithm and display the results
void CPU::Display::display(void (*algorithm)(DataStructure::Queue<CPU::Process> *, DataStructure::Queue<CPU::Process> *, DataStructure::Queue<CPU::Process> *), DataStructure::Queue<CPU::Process> *processes)
{
     DataStructure::Queue<CPU::Process> gantt, table;

     // Preform the scheduling algorithm
     algorithm(processes, &gantt, &table);

     // Display gantt chart
     Display::gantt(&gantt);
     // Display scheduled processes
     Display::table(&table);
     // Display the times
     Display::times(&table);
}
