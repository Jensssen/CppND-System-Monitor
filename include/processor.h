#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:

  float Utilization();

 private:
  int kUser_ = 0;
  int kNice_ = 0;
  int kSystem_ = 0;
  int kIdle_ = 0;
  int kIOwait_ = 0;
  int kIRQ_ = 0;
  int kSoftIRQ_ = 0;
  int kSteal_ = 0;

};

#endif