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
    else
    {
        std::string type = arg.substr( arg.find('<') + 1, arg.find('>') - 1 );
        std::string varName = arg.substr( arg.find('>') + 1 );
        
        if ( type == "int" )            std::cout << Variables::instance().getInt(varName) << std::endl;
        else if ( type == "string" )    std::cout << Variables::instance().getString(varName) << std::endl;
        else tedilang_exception("Nothing to output.");
    }

    return 0;
}

TEDILANG_FUNCTION("output", func_output)