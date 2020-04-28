#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
  return cpu_; }

bool compareProcesses(Process& p1, Process& p2) {
  int p1_ram = std::stoi(p1.Ram());
  int p2_ram = std::stoi(p2.Ram());
  return (p1_ram > p2_ram);
};

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  processes_.clear();
  for (int pID : LinuxParser::Pids()){
    string pRAM = LinuxParser::Ram(pID);
    string pCMD = LinuxParser::Command(pID);
    long pUpTime = LinuxParser::UpTime(pID);
    string user = LinuxParser::User(pID);

    Process process(pID, pRAM, pCMD, pUpTime, user);

    processes_.push_back(process);
  }
  std::sort(processes_.begin(), processes_.end(), compareProcesses);
  return processes_; }

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() {
  return LinuxParser::Kernel(); }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization(); }

// DONE: Return the operating system name
std::string System::OperatingSystem() {
  return LinuxParser::OperatingSystem(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long System::UpTime() {
  return LinuxParser::UpTime(); }