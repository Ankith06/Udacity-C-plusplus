#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

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
  string value, MemTotal, MemFree;
  float Memused;// MemAvailable, Buffers
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
          MemTotal = value;
      }
      if (key == "MemFree:") {
          //std::replace(value.begin(), value.end(), '_', ' ');
          MemFree = value;
      }
    }
  }
  Memused = std::stof(MemTotal) - std::stof(MemFree);
  float Memused_per = Memused/std::stof(MemTotal);
  return Memused_per; 

}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {     
  string line;
  string uptime;
  long Uptime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
    Uptime = std::stol(uptime);
  }
  return Uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// DONE: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  string key, utime, stime, cutime, cstime ;
  //int i = 0;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
    std::istringstream linestream(line);
    for(int i = 0; i < 13; i++) {
        linestream >> key; 
      }
    linestream >> utime >> stime >> cutime >> cstime;
    long totaltime = std::stol(utime)+std::stol(stime)+std::stol(cutime)+std::stol(cstime);
    return totaltime/sysconf(_SC_CLK_TCK);
    }
  }
  return -1;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string cpu, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> x1 >> x2 >> x3 >> x4 >> x5 >> x6 >> x7 >> x8 >> x9 >> x10;
  }
  vector<string> str = {x1, x2, x3, x4, x5, x6, x7, x8, x9, x10};
  return str;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
        return value;
      }
    }
  }
  return -1;
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        return value;
      }
    }
  }
  return value;
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
  }
  return "not found";
}

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        return std::to_string(std::stoi(value) / 1024);
      }
    }
  }
  return "not found";
}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        return value;
      }
    }
  }
  return "not found";
}

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string line, username, x, uid;
  string getuid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> username >> x >> uid;
      if (uid == getuid) {
        return username;
      }
    }
  }
  return "not found";
}

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  string line;
  string key;
  //int i = 0;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      for(int i = 0; i < 21; i++) {
        linestream >> key; 
      }
    linestream >> key;
    long uptime = std::stol(key)/sysconf(_SC_CLK_TCK);
    return uptime;
    }
  }
  return -1;
}
