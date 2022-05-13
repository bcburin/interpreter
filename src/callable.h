#ifndef CALLABLE_H
#define CALLABLE_H

#include "context.h"
#include "terminator.h"
#include <list>


class callable: public context {
  private:
    std::list<statement*> statements_;
    std::unordered_set<std::string> terminators_;
    context* parent_;
    inline bool is_terminator(std::string line);
  public:
    callable(context* parent, std::unordered_set<std::string> terminators = {"end"});
    ~callable();
    void call();
    virtual double get(std::string name);
    virtual void set(std::string name, double value);
    inline terminator* terminator_used();
};


/* IMPLEMENTATION */

bool callable::is_terminator(std::string line) { return terminators_.find(trim(line)) != terminators_.end(); }

terminator* callable::terminator_used() { return dynamic_cast<terminator*>(statements_.back()); }

#endif