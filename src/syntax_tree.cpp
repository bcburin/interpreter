#include "syntax_tree.h"
#include "binary_operator.h"
#include "helpers.h"

syntax_tree::syntax_tree(std::string str, context* contx)
: binary_tree(nullptr), str_(trim(str)), context_(contx), result_(nullptr) {
  // Check for empty expression
  if (str_ == "") return;
  // Validate input 
  validate();
  // Check if string is wrapped by a pair of parentheses; remove them if affirmative; repeat until not wrapped
  while (wrapped_by_parentheses()) str_ = str_.substr(1, str_.size()-2);
  // Check if str contains operator; traverse operators in increasing priority
  for(auto& op : binary_operator::set) {
    int index = find_outer_operator(op.str());
    if (index != std::string::npos) { // If operator was found
      data_ = new binary_operator(op);
      left_ = new syntax_tree(str_.substr(0,index), context_);
      right_ = new syntax_tree(str_.substr(index+op.str().size(),str_.size()-index-op.str().size()), context_);
      return;
    }
  }
  try{
    // If no operator was found, try to create tree node as number
    data_ = new numeric(str_);
  } catch(const std::invalid_argument& error) {
    // If it is not a number, initialize it as a variable
    data_ = new variable(str_, context_);
  }
}

syntax_tree::syntax_tree(const syntax_tree& other): binary_tree<token*>(other) {}

syntax_tree::syntax_tree(syntax_tree&& other): binary_tree<token*>(std::move(other)) {}

syntax_tree::~syntax_tree() { delete result_; /*delete data_;*/ }


operand* syntax_tree::parse() {
  // Base case: operand node
  if (auto operand_node = dynamic_cast<operand*>(data_)) 
    return result_ = operand_node;
  // Base case: empty tree
  if(is_empty()) return nullptr;
  // If it is not an operand node, it is an operator node
  auto left_tree = static_cast<syntax_tree*>(left_);
  auto right_tree = static_cast<syntax_tree*>(right_);
  auto op = *static_cast<binary_operator*>(data_);
  // Recursive calculation
  return result_ = op(left_tree->parse(),right_tree->parse());
}

void syntax_tree::validate() {
  // Validate parentheses
  int open_pars = 0;
  for (const auto& ch : str_) {
    if (ch == '(') ++open_pars;
    if (ch == ')') --open_pars;
    // Check for closing of unopened parentheses
    if (open_pars < 0) throw std::invalid_argument("Closed unopened parentheses.");
  }
  // Check for unclosed parentheses
  if (open_pars > 0) throw std::invalid_argument("Unclosed parentheses.");
}

bool syntax_tree::wrapped_by_parentheses() {
  // Check if first char is an open parenthesis
  if(str_[0] != '(') return false;
  // Determine end of first expression wrapped by parentheses
  int i, open_pars = 1;
  for (i = 1; i != str_.size() && open_pars != 0 ; ++i) {
    if (str_[i] == '(') ++open_pars;
    if (str_[i] == ')') --open_pars;
  }
  // Return true if initial open parenthesis is closed at the end of string
  return i == str_.size();
}

int syntax_tree::find_outer_operator(std::string op_str) {
  //Track number of opened/closed parentheses while traversing the string
  int nested_pars = 0;
  for (int i = 0; i != str_.size(); ++i) {
    // Update tracker of nested parentheses
    if(str_[i] == '(') ++nested_pars;
    if(str_[i] == ')') --nested_pars;
    // Search string only if outside any parentheses
    if(nested_pars == 0) {
      bool found = true;
      for (int j = 0; j != op_str.size(); ++j) {
        if(op_str[j] != str_[i+j]) {
          found = false;
          break;
        }
      }
      if (found) return i;
    }
  }
  return std::string::npos;
}
