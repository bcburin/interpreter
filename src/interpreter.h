#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "context.h"
#include "statement.h"

struct interpreter: public context {
  interpreter(std::istream* is_, std::ostream* os_);
  void run();
};


#endif