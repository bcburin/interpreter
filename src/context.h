#ifndef CONTEXT_H
#define CONTEXT_H

#include "helpers.h"
#include <unordered_map>
#include <exception>
#include <iostream>

class context {
  protected:
    std::unordered_map<std::string, double> variables_;
    std::istream* is_;
    std::ostream* os_;
    context* parent_;
  public:
    context(std::istream* is_, std::ostream* os_ = nullptr, context* parent = nullptr);
    void display(std::string str, bool endl=false);
    void display(double value, bool endl=false);
    virtual double get(std::string var_name);
    virtual void set(std::string var_name, double value);
    inline bool contains(std::string var_name);
    inline std::istream* input();
    inline std::ostream* output();
    inline context* parent();
};


/* IMPLEMENTATION */

std::istream* context::input() { return is_; }
std::ostream* context::output() { return os_; }
context* context::parent() { return parent_; }
bool context::contains(std::string var_name) { return variables_.find(var_name) != variables_.end();  }

#endif
