#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_parser.hpp"
#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"
#include "core/tedilang_interpreter.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

#include "variables.hpp"

int main( int argc, char* argv[] ) {
    if ( argc == 1 ) tedilang_exception("Specify file or argument.");
    
    if ( argv[1] && argv[1][0] == '-' ) tedilang_argument(argv[1]);

    std::ifstream file( argv[1] );

    if (!file.is_open()) tedilang_exception("File not exist.");

    tedilang_parser(file);

    file.close();
    return 0;
}