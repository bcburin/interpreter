#include "statement.h"
#include "if_statement.h"
#include "while_statement.h"
#include "expression.h"
#include "helpers.h"

statement::statement(std::string str, context* contx): str_(str), context_(contx) {}

statement* statement::interpret(std::string line, context* contx) {
  line = trim(line);
  if(line == "") return nullptr;
  if(starts_with(line, if_statement::keyword_if)) return new if_statement(line, contx);
  if(starts_with(line, while_statement::keyword_while)) return new while_statement(line, contx);
  return new expression(line, contx);
}

std::string statement::str() { return trim(str_); }
