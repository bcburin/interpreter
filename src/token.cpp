#include "token.h"

token::token(std::string str): str_(str) {}

std::ostream& operator<<(std::ostream& os, const token& tk) { return os << tk.str(); }