#ifndef WHILE_STATEMENT_H
#define WHILE_STATEMENT_H

#include "statement.h"
#include "expression.h"
#include "callable.h"

class while_statement: public statement {
  private:
    std::string condition_;
    callable* body_;
  public:
    static const std::string keyword_while;
    while_statement(std::string str, context* contx);
    ~while_statement();
    void execute() override;
};


const std::string while_statement::keyword_while = "while ";

while_statement::while_statement(std::string str, context* contx)
: statement(str, contx), body_(nullptr) {
  // Read condition
  condition_ = str.substr(keyword_while.size());
  // Create callable body
  body_ = new callable(contx);
}

while_statement::~while_statement() { delete body_; }

void while_statement::execute() {
  while( expression(condition_, context_).result() ) body_->call();
}

#endif