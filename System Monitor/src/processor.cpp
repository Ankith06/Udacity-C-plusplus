#include "processor.h"
#include "linux_parser.h"

using std::stof;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
 
  std::vector<std::string> cpu = LinuxParser::CpuUtilization();
  float user   = std::stof(cpu[0]);
  float nice   = std::stof(cpu[1]);
  float system = std::stof(cpu[2]);
  float idle   = std::stof(cpu[3]);
  float iowait = std::stof(cpu[4]);
  float irq    = std::stof(cpu[5]);
  float softirq   = std::stof(cpu[6]);
  float steal     = std::stof(cpu[7]);
  float guest     = std::stof(cpu[8]);
  float guest_nice   = std::stof(cpu[9]);
  
  user = user - guest;                   
  nice = nice - guest_nice; 
  
  float idlealltime = idle + iowait;                 
  float systemalltime = system + irq + softirq;
  float virtalltime = guest + guest_nice;
  float totaltime = user + nice + systemalltime + idlealltime + steal + virtalltime;
  
  return (totaltime - idlealltime)/totaltime;
}
