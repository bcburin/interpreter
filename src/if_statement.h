#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

#include "statement.h"
#include "expression.h"
#include "callable.h"

class if_statement: public statement {
  private:
    std::string condition_;
    callable* if_body_;
    callable* else_body_;
  public:
    static const std::string keyword_if;
    static const std::string keyword_else;
    if_statement(std::string str, context* contx);
    ~if_statement();
    void execute() override;
};

const std::string if_statement::keyword_if = "if ";
const std::string if_statement::keyword_else = "else";

if_statement::if_statement(std::string str, context* contx)
: statement(str, contx), if_body_(nullptr), else_body_(nullptr) {
  // Read condition
  condition_ = str.substr(keyword_if.size());
  // Create callable if body
  if_body_ = new callable(contx, {"else", "end"});
  // Create else body
  if( auto if_terminator = if_body_->terminator_used() )
    if( if_terminator->str() == "else" ) {
      else_body_ = new callable(contx); 
    }
}

if_statement::~if_statement() {
  delete if_body_;
  delete else_body_;
}

void if_statement::execute() {
  if( expression(condition_, context_).result() ) if_body_->call();
  else if(else_body_) else_body_->call();
}


#endif