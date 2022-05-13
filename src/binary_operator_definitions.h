#ifndef BINARY_OPERATOR_DEFINITIONS_H
#define BINARY_OPERATOR_DEFINITIONS_H

#include "binary_operator.h"

operation sum__ = [](operand* x, const operand* y){ 
  if(!y) throw std::invalid_argument("Expected expression after + operator.");
  if(!x) return new numeric(y->value());
  return new numeric(x->value() + y->value()); 
};

operation sub__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after - operator.");
  if(!x) return new numeric(-(y->value()));
  return new numeric(x->value() - y->value()); 
};

operation mul__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after * operator.");
  if(!x) throw std::invalid_argument("Expected expression before * operator.");
  return new numeric(x->value() * y->value()); 
};

operation div__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after / operator.");
  if(!x) throw std::invalid_argument("Expected expression before / operator.");
  if (y->value() == 0) throw std::invalid_argument("Division by zero.");
  return new numeric(x->value() / y->value()); 
};

operation or__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after || operator.");
  if(!x) throw std::invalid_argument("Expected expression before || operator.");
  return new numeric(x->value() || y->value()); 
};

operation and__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after && operator.");
  if(!x) throw std::invalid_argument("Expected expression before && operator.");
  return new numeric(x->value() && y->value()); 
};

operation lt__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after < operator.");
  if(!x) throw std::invalid_argument("Expected expression before < operator.");
  return new numeric(x->value() < y->value()); 
};

operation gt__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after > operator.");
  if(!x) throw std::invalid_argument("Expected expression before > operator.");
  return new numeric(x->value() > y->value()); 
};

operation le__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after <= operator.");
  if(!x) throw std::invalid_argument("Expected expression before <= operator.");
  return new numeric(x->value() <= y->value()); 
};

operation ge__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after >= operator.");
  if(!x) throw std::invalid_argument("Expected expression before >= operator.");
  return new numeric(x->value() >= y->value()); 
};

operation eq__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after == operator.");
  if(!x) throw std::invalid_argument("Expected expression before == operator.");
  return new numeric(x->value() == y->value()); 
};

operation ne__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after != operator.");
  if(!x) throw std::invalid_argument("Expected expression before != operator.");
  return new numeric(x->value() != y->value()); 
};

operation not__ = [](operand* x, const operand* y){
  if(!y) throw std::invalid_argument("Expected expression after ! operator.");
  if(x) throw std::invalid_argument("Unexpected expression before ! operator.");
  return new numeric( !(y->value()) ); 
};

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

operation operation_assign(std::string op_name, operation& __op__) {
  return [op_name, &__op__](operand* left, const operand* right){ 
    if(!right) throw std::invalid_argument("Expected expression after " + op_name + " operator.");
    if(!left) throw std::invalid_argument("Expected variable before " + op_name + " operator.");
    numeric* result = __op__(left, right);
    return assign__(left, result);
  };
}

operation sum_assign__ = operation_assign("+=", sum__);
operation sub_assign__ = operation_assign("-=", sub__);
operation mul_assign__ = operation_assign("*=", mul__);
operation div_assign__ = operation_assign("/=", div__);

#endif