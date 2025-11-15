#include "register_function.hpp"
#include "function_registry.hpp"
#include "variables.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_utils.hpp"

#include <iostream>

ReturnType func_output( std::string arg ) {
    
    if ( is_string(arg) ) {
        std::cout << remove_qm( arg ) << std::endl;
    }
    else if ( is_function(arg) )
    {
        std::cout << FunctionRegistry::instance().run( get_function_name(arg), get_function_args(arg) ) << std::endl;
    }
    else if ( Variables::instance().isDeclaredVariable(arg) )
    {
        switch (Variables::instance().getVarType(arg)) {
            case Variables::Type::INT:
                std::cout << Variables::instance().getInt(arg) << std::endl;
                break;

            case Variables::Type::STRING:
                std::cout << Variables::instance().getString(arg) << std::endl;
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