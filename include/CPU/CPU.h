class CPU
{
public:
#include "classes/Process.h"

#include "classes/Algorithm.h"

#include "classes/Display.h"

     // Set data on the basis of given table
     static Queue<CPU::Process> sample_data()
     {
          Queue<CPU::Process> queue;

          queue.push(CPU::Process(1, 0, 6));
          queue.push(CPU::Process(2, 0, 2));
          queue.push(CPU::Process(3, 0, 5));
          queue.push(CPU::Process(4, 0, 3));
          queue.push(CPU::Process(5, 0, 6));

          return queue;
     }
};
