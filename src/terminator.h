#ifndef TERMINATOR_H
#define TERMINATOR_H

#include "statement.h"
#include <string>
#include <unordered_set>


struct terminator: public statement {
  terminator(std::string str);
  void execute() override;
};


#endif