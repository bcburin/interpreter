#include "binary_operator.h"
#include "binary_operator_definitions.h"

binary_operator::binary_operator(std::string str, int priority, operation apply)
: token(str), priority_(priority), apply_(apply) {}

numeric* binary_operator::operator()(operand* op1, const operand* op2) const { 
  return apply_(op1, op2); 
}

bool operator<(const binary_operator& op1, const binary_operator& op2) {
  return op1.priority() < op2.priority();
}




std::set<binary_operator> binary_operator::set = {
  binary_operator("=", 16, assign__),
  binary_operator("+", 24, sum__),
  binary_operator("-", 32, sub__),
  binary_operator("*", 40, mul__),
  binary_operator("/", 48, div__),
};