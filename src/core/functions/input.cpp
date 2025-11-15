#include "register_function.hpp"
#include "function_registry.hpp"
#include "variables.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_utils.hpp"

#include <iostream>

ReturnType func_input( std::string arg ) {
    if ( is_string(arg) ) {
        FunctionRegistry::instance().run( "output", arg );
    }

    std::string x;
    std::cin >> x;
    return x;
}

TEDILANG_FUNCTION("input", func_input)