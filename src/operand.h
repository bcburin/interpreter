#ifndef OPERAND_H
#define OPERAND_H

#include "token.h"
#include "callable.h"
#include <stdexcept>

struct operand: public token { 
  operand(std::string str);
  virtual double value() const = 0;
};


class numeric: public operand {
  private:
    double value_;
  public:
    numeric(std::string str);
    numeric(double value);
    double value() const override;
};


class variable: public operand {
  private:
    std::string name_;
    context* context_;
    void validate_name();
  public:
    variable(std::string name, context* contx);
    double value() const override;
    void set(double value);
};


#endif