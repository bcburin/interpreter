#include "interpreter.h"

interpreter::interpreter(std::istream* is, std::ostream* os)
    : context(is, os) {}

void interpreter::run() {
    // Print input marker
    display(">> ");
    // Read lines
    std::string line;
    while (std::getline(*is_, line) && trim(line) != "end") {
        try {
            // Interpret statement
            auto st = statement::interpret(line, this);
            // Execute statement
            if (st) st->execute();
        } catch (std::invalid_argument& error) {
            std::cout << "   " << error.what() << std::endl;
        }
        // Print input marker
        display(">> ");
    }
}
