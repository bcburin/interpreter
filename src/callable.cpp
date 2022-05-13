#include "callable.h"

callable::callable(context* parent, std::unordered_set<std::string> terminators)
: context(parent->input(), parent->output()), parent_(parent), terminators_(terminators) {
  // Print input marker
  if(os_) *os_ << ">> ";
  // Read lines
  std::string line;
  while ( std::getline(*is_, line) && !is_terminator(line) ) {
    // Store statements
    statements_.push_back(statement::interpret(line, this));
    // Print input marker
    if(os_) *os_ << ">> ";
  }
  // Store terminator line
  if(is_terminator(line)) statements_.push_back(new terminator(line));
}

callable::~callable() { 
  for (auto st : statements_) delete st;
}

void callable::call() {
  for (auto st : statements_) st->execute();
}

double callable::get(std::string name) {
  // Look for value in it and its parents
  for(callable* search = this; search; search = dynamic_cast<callable*>(search->parent_)) {
    if(search->contains(name)) return search->get(name);
  }
  // Variable undefined
  throw std::invalid_argument("Undefined variable: '" + name + "'");
}

void callable::set(std::string name, double value) {
  // Look for value in its parents
  for(callable* search = this; search; search = dynamic_cast<callable*>(search->parent_)) {
    if(search->contains(name)) {
      search->set(name, value);
      return;
    }
  }
  // If not found, create variable in current context
  context::set(name, value);
}