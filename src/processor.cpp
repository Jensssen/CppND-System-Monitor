#include "processor.h"
#include <vector>
#include <iomanip>


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<float> cpuUtil = LinuxParser::CpuUtilization();

  float user = cpuUtil[0];
  float nice = cpuUtil[1];
  float system = cpuUtil[2];
  float idle = cpuUtil[3];
  float iowait = cpuUtil[4];
  float irq = cpuUtil[5];
  float softirq = cpuUtil[6];
  float steal = cpuUtil[7];

  float PrevIdle = kIdle_ + kIOwait_;
  float Idle = idle + iowait;

  float PrevNonIdle = kUser_ + kNice_+ kSystem_ + kIRQ_ + kSoftIRQ_ + kSteal_;
  float NonIdle = user + nice + system + irq + softirq + steal;

  float PrevTotal = PrevIdle + PrevNonIdle;
  float Total = Idle + NonIdle;

  float totald = Total - PrevTotal;

  float idled = Idle - PrevIdle;

  float CPU_Percentage = (totald - idled) / totald;

  return CPU_Percentage;
}