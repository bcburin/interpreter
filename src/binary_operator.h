#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "operand.h"
#include "context.h"
#include <set>
#include <functional>

using operation = std::function<numeric*(const operand*, const operand*)>;

class binary_operator: public token{
  private:
    int priority_;
    operation apply_;
  public:
    binary_operator(std::string str, int priority, operation apply);
    numeric* operator()(const operand*, const operand*) const;
    inline int priority() const;
    inline operation apply() const;
    static std::set<binary_operator> set;
};

bool operator<(const binary_operator&, const binary_operator&);

/* IMPLEMENTATION */

int binary_operator::priority() const { return priority_; }
operation binary_operator::apply() const { return apply_; }

#endif