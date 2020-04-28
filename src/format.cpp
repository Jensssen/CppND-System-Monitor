#include <string>
#include "format.h"
#include <sstream>
#include <iomanip>
using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  long s = seconds % 60;
  long m = (seconds / 60) % 60;
  long h = (seconds / (60 * 60)) % 24;
  return std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s);
}

string Format::kbToMb(int kb){
  float mb = kb / 1024.0;
  std::stringstream mb_stream;
  mb_stream << std::fixed << std::setprecision(1) << mb;
  return mb_stream.str();
}