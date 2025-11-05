#include "register_function.hpp"
#include "variables.hpp"
#include "core/tedilang_helpers.hpp"

#include <iostream>

void func_output( std::string arg ) {
    if ( is_string(arg) ) {
        std::cout << remove_qm( arg ) << std::endl;
    } 
    else
    {
        std::string type = arg.substr( 0, arg.find('@') );
        std::string varName = arg.substr( arg.find('@') + 1 );
        
        if ( type == "int" )            std::cout << Variables::instance().getInt(varName) << std::endl;
        else if ( type == "string" )    std::cout << Variables::instance().getString(varName) << std::endl;
        else std::cerr << "[ERROR] Nothing to output." << std::endl;
    }
}

TEDILANG_FUNCTION("output", func_output)