#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "binary_tree.h"
#include "context.h"
#include "operand.h"

class syntax_tree: public binary_tree<token*> {
  protected:
    std::string str_;
    context* context_;
    operand* result_;
    void validate();
    bool wrapped_by_parentheses();
    int find_outer_operator(std::string op_str);
  public:
    syntax_tree(std::string str, context* contx);
    syntax_tree(const syntax_tree& other);
    syntax_tree(syntax_tree&& other);
    ~syntax_tree();
    operand* parse();
    inline double result();
    inline bool is_empty();
};


bool syntax_tree::is_empty() { return !data_; }

double syntax_tree::result() { return parse()->value(); }


#endif