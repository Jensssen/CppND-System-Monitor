#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "format.h"
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

template <typename T>
T getValueFromKey(string const &filePath, string const &filterKey){
  string line;
  string key;
  T value;
  std::ifstream filestream(filePath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterKey) {
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float memTotal;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          memTotal = std::stof(value);
        }
        if (key == "MemFree") {
          return (memTotal - std::stof(value)) / memTotal;
        }
      }
    }
  }
  return 0.0;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        return std::stol(key);
      }
    }
  }
  return 0; }

// TODO: Read and return CPU utilization
vector<float> LinuxParser::CpuUtilization() {
  string line, key, value;
  vector<float> cpuUtil;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> key) {
      if (key == "cpu") { // TODO: Replace all strings with consts
        while (linestream >> value) {
          cpuUtil.emplace_back(std::stof(value));
        }
      }
    }
  }
  return cpuUtil;
}

float LinuxParser::CpuUtilization(int pid) {
  string line, value;
  vector<std::string> cpuUtil;
  std::ifstream stream(kProcDirectory +std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
          cpuUtil.emplace_back(value);
    }
  }
  float hertz = sysconf(_SC_CLK_TCK);
  float utime = std::stof(cpuUtil[13]);
  float stime = std::stof(cpuUtil[14]);
  float cutime = std::stof(cpuUtil[15]);
  float cstime = std::stof(cpuUtil[16]);
  float starttime = std::stof(cpuUtil[21]) / hertz; // Starttime of the process in seconds
  long upTime = UpTime(); // Time how long the PC is running in seconds

  float seconds = upTime - starttime; // Time, how long the process is already running
  float total_time = utime + stime + cutime + cstime;
  return (total_time / hertz) / seconds;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  return getValueFromKey<int>(kProcDirectory + kStatFilename, "processes");
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  return getValueFromKey<int>(kProcDirectory + kStatFilename, "procs_running");
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string line;
  string cmd;
  string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> cmd) {
          return cmd;
      }
    }
  }
  return string(); }

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid ) {
  string ram = getValueFromKey<std::string>(kProcDirectory + std::to_string(pid) + kStatusFilename, "VmSize:");
  return Format::kbToMb(std::stoi(ram));
}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
    return getValueFromKey<std::string>(kProcDirectory + std::to_string(pid) + kStatusFilename, "Uid:");
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line;
  string key;
  string x, value;
  string uid = Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> x >> value) {
        if (key == uid) {
          return value;
        }
      }
    }
  }
  return string();
}

// Done: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  string line, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i = 0;
    while (linestream >> value)
    {
      if(i == 21){
          return UpTime() - (std::stol(value) / sysconf(_SC_CLK_TCK));
      }else{
        i++;
      }
    }
  }
  return 0;
}