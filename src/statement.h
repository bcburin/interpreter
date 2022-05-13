#ifndef STATEMENT_H
#define STATEMENT_H

#include "context.h"
#include <string>

class statement {
  protected:
    std::string str_;
    context* context_;
  public:
    statement(std::string str, context* contx = nullptr);
    inline std::string str();
    virtual void execute() = 0;
    static statement* interpret(std::string line, context* contx);
};



#endif