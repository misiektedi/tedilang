#include "register_function.hpp"
#include "function_registry.hpp"
#include "variables.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_utils.hpp"

#include <iostream>

ReturnType func_output( std::vector<std::string> arg ) {

    std::string str = arg[0];
    
    if ( is_string(str) ) {
        std::cout << remove_qm( str ) << std::endl;
    }
    else if ( is_function(str) )
    {
        std::cout << FunctionRegistry::instance().run( get_function_name(str), get_function_args(str) ) << std::endl;
    }
    else if ( Variables::instance().isDeclaredVariable(str) )
    {
        switch (Variables::instance().getVarType(str)) {
            case Variables::Type::INT:
                std::cout << Variables::instance().getInt(str) << std::endl;
                break;

            case Variables::Type::STRING:
                std::cout << Variables::instance().getString(str) << std::endl;
                break;

            default:
                tedilang_exception("Nothing to output.");
                break;
        }
    }
    else
    {
        tedilang_exception("Invalid output() usage.");
    }

    return 0;
}

TEDILANG_FUNCTION("output", func_output)