#ifndef BINARY_OPERATOR_DEFINITIONS_H
#define BINARY_OPERATOR_DEFINITIONS_H

#include "binary_operator.h"

operation sum__ = [](operand* op1, const operand* op2){ return new numeric(op1->value() + op2->value()); };
operation sub__ = [](operand* op1, const operand* op2){ return new numeric(op1->value() - op2->value()); };
operation mul__ = [](operand* op1, const operand* op2){ return new numeric(op1->value() * op2->value()); };
operation div__ = [](operand* op1, const operand* op2){ return new numeric(op1->value() / op2->value()); };

operation assign__ = [](operand* left, const operand* right) {
  // Read left hand side operand as variable
  auto var = dynamic_cast<variable*>(left);
  // If it is not a variable, throw an exception
  if(!var) throw std::invalid_argument("Left hand side of assigment operator (" + left->str() + ") must bu a variable.");
  // Carry out assignment
  var->set(right->value());
  // Cascade result
  return new numeric(right->value());
};

#endif