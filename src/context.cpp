#include "context.h"

context::context(std::istream* is, std::ostream* os, context* parent)
: is_(is), os_(os), parent_(parent) {}

double context::get(std::string var_name) {
  if(!contains(var_name)) throw std::invalid_argument("Undefined variable: '" + var_name + "'");

  return variables_[var_name];
}

void context::set(std::string var_name, double value) {
  variables_[var_name] = value;
}