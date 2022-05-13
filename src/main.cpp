#include "interpreter.h"
#include "binary_operator.h"
#include "syntax_tree.h"

int main() {
  interpreter global(&std::cin, &std::cout);

  global.run();

  return 0;
}