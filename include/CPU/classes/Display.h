class Display
{
private:
     static void repeat(char c, uint16_t num)
     {
          for (uint8_t j = 0; j < num; j++)
               Serial.print(c);
     }

     static void printCol(int attr, uint8_t left, uint8_t right)
     {

          uint8_t temp = countDigit(attr);

          left = left - temp / 2 - temp % 2;
          right = right - temp / 2;

          repeat(' ', right);

          Serial.print(attr);

          repeat(' ', left);

          Serial.print("|");
     }

     static void printLine(bool p)
     {
          Serial.print("+-------------+--------------+------------+-----------------+-----------------+--------------+---------------+");

          if (p == true)
               Serial.print("----------+");
          Serial.println();
     }

public:
     // return number of digits
     static int countDigit(int n)
     {
          if (n == 0)
               return 1;

          int count = 0;

          if (n < 0)
               n = -n, count++;

          while (n > 0)
               n = n / 10, count++;

          return count;
     }

     // Function to display Completion Queue and all the time
     static void table(Queue<CPU::Process> processes, bool p = true)
     {

          printLine(p);

          Serial.print("| Process No. | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Response Time |");

          if (p == true)
               Serial.print(" Priority |");
          Serial.println();

          printLine(p);

          while (processes.notEmpty())

          {
               CPU::Process process = processes.pop();

               Serial.print("|");

               printCol(process.id, 7, 6);

               printCol(process.initial_arrival_time, 7, 7);

               printCol(process.burst_time, 6, 6);

               printCol(process.completion_time, 9, 8);

               printCol(process.turnaround_time, 9, 8);

               printCol(process.waiting_time, 7, 7);

               printCol(process.response_time, 8, 7);

               if (p == true)
                    printCol(processes.front().priority, 5, 5);

               Serial.println();
          }

          printLine(p);

          Serial.println("\n");
     }

     static void times(Queue<CPU::Process> processes)
     {
          uint16_t size = processes.size();

          double temp;

          temp = CPU::Algorithm::get_total_completion_time(processes);

          Serial.print("Total Completion Time: ");
          Serial.println(temp);

          Serial.print("Average Completion Time: ");
          Serial.println(temp / size);

          Serial.println();

          temp = CPU::Algorithm::get_total_turnaround_time(processes);

          Serial.print("Total Turnaround Time: ");
          Serial.println(temp);

          Serial.print("Average Turnaround Time: ");
          Serial.println(temp / size);

          Serial.println();

          temp = CPU::Algorithm::get_total_waiting_time(processes);

          Serial.print("Total Waiting Time: ");
          Serial.println(temp);

          Serial.print("Average Waiting Time: ");
          Serial.println(temp / size);

          Serial.println();

          temp = CPU::Algorithm::get_total_reponse_time(processes);

          Serial.print("Total Response Time: ");
          Serial.println(temp);

          Serial.print("Average Response Time: ");
          Serial.println(temp / size);
     }

     // Function to display Gantt Chart
     static void gantt(Queue<CPU::Process> gantt)
     {

          Queue<CPU::Process> processes = gantt;

          Serial.print("Gantt Chart (IS indicates ideal state) :- \n\n+");

          // For 1st row of gantt chart
          while (processes.notEmpty())
          {
               CPU::Process process = processes.pop();

               repeat('-', countDigit(process.id) + (process.id != -1) + 2 * process.temp_burst_time);

               Serial.print("+");
          }

          Serial.print("\n|");

          processes = gantt;

          // For process no. in 2nd row
          while (processes.notEmpty())
          {
               CPU::Process process = processes.pop();

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
          }

          Serial.print("\n+");

          processes = gantt;

          while (processes.notEmpty())
          {
               CPU::Process process = processes.pop();

               repeat('-', countDigit(process.id) + (process.id != -1) + 2 * process.temp_burst_time);

               Serial.print("+");
          }

          Serial.print("\n0");

          processes = gantt;

          int temp, prev = 0;

          //For 3rd row of gantt chart
          while (processes.notEmpty())
          {
               CPU::Process process = processes.pop();

               temp = countDigit(process.completion_time);

               repeat(' ', countDigit(process.id) + (process.id != -1) + 2 * process.temp_burst_time - temp / 2 - prev);

               Serial.print(process.completion_time);

               prev = temp / 2 - temp % 2 == 0;
          }

          Serial.print("\n\n");
     }

     // Preform the Algorithm and display the results
     static void display(void (*algorithm)(Queue<CPU::Process>, Queue<CPU::Process> *, Queue<CPU::Process> *), Queue<CPU::Process> processes)
     {
          Queue<CPU::Process> gantt, table;

          // Preform the scheduling algorithm
          algorithm(processes, &gantt, &table);

          // Display gantt chart
          Display::gantt(gantt);

          // Display scheduled processes
          Display::table(table);

          // Display the times
          Display::times(table);
     }
};