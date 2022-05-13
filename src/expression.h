#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "statement.h"
#include "interpreter.h"
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
  // Pase expression
  parse();
  // Display result if in interpreter shell
  if(auto interpreter_context = dynamic_cast<interpreter*>(statement::context_))
    interpreter_context->display(result_->value(), true);
}


#endif