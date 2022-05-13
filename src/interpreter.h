#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "context.h"
#include "statement.h"

struct interpreter: public context {
  interpreter(std::istream* is_, std::ostream* os_);
  void run();
};


/* IMPLEMENTATION */

interpreter::interpreter(std::istream* is, std::ostream* os)
: context(is, os) {}

void interpreter::run() {
  // Print input marker
  if(os_) *os_ << ">> ";
  // Read lines
  std::string line;
  while ( std::getline(*is_, line) && trim(line) != "end" ) {
    // Interpret statement
    auto st = statement::interpret(line, this);
    // Execute statement
    if(st) st->execute();
    // Print input marker
    if(os_) *os_ << ">> ";
  }
}


#endif