#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, std::string ram, std::string cmd, long upTime, std::string user, float cpuUtil)
      : pid_(pid), ram_(ram), cmd_(cmd), upTime_(upTime), user_(user), cpuUtil_(cpuUtil){};
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram() const;
  long int UpTime();
  bool operator<(Process const& process) const;

 private:
  int pid_ = 0;
  std::string ram_ = "";
  std::string cmd_ = "";
  long upTime_ = 0;
  std::string user_ = "";
  float cpuUtil_ = 0.0;
};

#endif