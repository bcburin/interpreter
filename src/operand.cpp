#include "operand.h"

operand::operand(std::string str): token(str) {}


numeric::numeric(std::string str): operand(str) {
  try { value_ = std::stod(str); }
  catch(...) { throw std::invalid_argument("Operand not convertible to number."); }
}

numeric::numeric(double value): operand(std::to_string(value)), value_(value) {}

double numeric::value() const { return value_; }


variable::variable(std::string name, context* contx)
: operand(name), name_(trim(name)), context_(contx) { validate_name(); }

double variable::value() const { return context_->get(name_); }

void variable::set(double value) { context_->set(name_, value); }

void variable::validate_name() {
  // Variable name must start with letter or _ character
  if (!isalpha(name_[0]) && name_[0] != '_') 
    throw std::invalid_argument("Invalid variable name: '" + name_ + "' (must start with a letter or _ character).");
  // Variable name must be made up by letters, numbers or the _ character
  for (const auto& ch : name_)
    if(!isalnum(ch) && ch != '_')
      throw std::invalid_argument("Invalid variable name: '" + name_ + "' (must contain letters, numbers or the _ character only).");
}
