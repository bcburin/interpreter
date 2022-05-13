#include "statement.h"
#include "if_statement.h"
#include "expression.h"
#include "helpers.h"

statement::statement(std::string str, context* contx): str_(str), context_(contx) {}

statement* statement::interpret(std::string line, context* contx) {
  // Remove whitespace
  line = trim(line);
  // Empty input
  if(line == "") return nullptr;
  // If statement
  if(starts_with(line, "if ")) return new if_statement(line, contx);
  // Dafautl case: expression
  return new expression(line, contx);
}

std::string statement::str() { return trim(str_); }
