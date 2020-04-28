#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, std::string ram, std::string cmd, long upTime, std::string user)
      : pid_(pid), ram_(ram), cmd_(cmd), upTime_(upTime), user_(user){};
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  // TODO: Declare any necessary private members
 private:
  int pid_ = 0;
  std::string ram_ = "";
  std::string cmd_ = "";
  long upTime_ = 0;
  std::string user_ = "";
  float cpuUtil_ = 0.0;
};

#endif