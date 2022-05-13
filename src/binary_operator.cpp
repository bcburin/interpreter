#include "binary_operator.h"

binary_operator::binary_operator(std::string str, int priority, operation apply)
: token(str), priority_(priority), apply_(apply) {}

numeric* binary_operator::operator()(const operand* op1, const operand* op2) const { 
  return apply_(op1, op2); 
}

bool operator<(const binary_operator& op1, const binary_operator& op2) {
  return op1.priority() < op2.priority();
}

operation sum__ = [](const operand* op1, const operand* op2){ return new numeric(op1->value() + op2->value()); };
operation sub__ = [](const operand* op1, const operand* op2){ return new numeric(op1->value() - op2->value()); };
operation mul__ = [](const operand* op1, const operand* op2){ return new numeric(op1->value() * op2->value()); };
operation div__ = [](const operand* op1, const operand* op2){ return new numeric(op1->value() / op2->value()); };

std::set<binary_operator> binary_operator::set = {
  binary_operator("+", 24, sum__),
  binary_operator("-", 32, sub__),
  binary_operator("*", 40, mul__),
  binary_operator("/", 48, div__),
};