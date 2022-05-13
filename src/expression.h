#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "statement.h"
#include "syntax_tree.h"


class expression: public statement, public syntax_tree {
private:
  /* data */
public:
  expression(std::string str, context* contx);
  void execute() override;
};


expression::expression(std::string str, context* contx)
: statement(str, contx), syntax_tree(str, contx) {}

void expression::execute() {
  *statement::context_->output() << parse()->value()  << std::endl;
}


#endif