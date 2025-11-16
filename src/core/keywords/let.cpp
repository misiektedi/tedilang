#include "register_keyword.hpp"
#include "keyword_registry.hpp"
#include "function_registry.hpp"

#include "core/impl/calc.hpp"
#include "core/tedilang_helpers.hpp"

#include "variables.hpp"

#include <iostream>

ReturnType key_let( std::string arg ) {
    std::array<std::string, 2> types    = {"int", "string"};

    std::string type                    = arg.substr(0, 0 + arg.find(' ') );

    std::string content                 = arg.substr(1 + type.length());

    size_t pos                          = content.find('=');

    std::string key                     = content.substr(0, -1 + pos);
    std::string value                   = content.substr(pos + 1);

    value                               = string_trim(value);

    if ( is_function( value ) ) {
        FunctionRegistry::instance().run( get_function_name(value), get_function_args(value) );
        value = std::get<std::string>(FunctionRegistry::instance().result);
    }
    
    if ( type == "int" )            Variables::instance().setInt( key, calc(value) );
    else if ( type == "string" )    Variables::instance().setString( key, remove_qm(value) );

    return std::monostate{};
}

TEDILANG_KEYWORD("let", key_let)