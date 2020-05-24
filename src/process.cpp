#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid() {
  return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtil_; }

// DONE: Return the command that generated this process
string Process::Command() { return cmd_; }

// DONE: Return this process's memory utilization
string Process::Ram() const { return ram_; }

// DONE: Return the user (name) that generated this process
string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return upTime_; }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& process) const { return std::stoi(this->Ram()) < std::stoi(process.Ram()); }