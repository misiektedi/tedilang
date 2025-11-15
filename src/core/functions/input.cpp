#include "register_function.hpp"
#include "function_registry.hpp"
#include "variables.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_utils.hpp"

#include <iostream>

ReturnType func_input( std::vector<std::string> arg ) {

    std::string str = arg[0];

    if ( is_string(str) ) {
        FunctionRegistry::instance().run( "output", str );
    }

    std::string x;
    std::cin >> x;
    return x;
}

TEDILANG_FUNCTION("input", func_input)