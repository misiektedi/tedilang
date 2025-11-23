#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

#include "variables.hpp"
#include "core/impl/calc.hpp"

void tedilang_variables_handler( std::string x ) {
    size_t pos          = x.find('=');

    std::string name    = x.substr(0, pos - 1);
    std::string value   = x.substr(pos + 1, x.length());

    name                = string_trim(name);
    value               = string_trim(value);

    if ( is_function( value ) ) {
        FunctionRegistry::instance().run( get_function_name(value), get_function_args(value) );
        value = std::get<std::string>(FunctionRegistry::instance().result);
    }

    switch (Variables::instance().getVarType(name)) {
        case Variables::Type::INT:
            Variables::instance().setInt(name, calc(value));
            break;

        case Variables::Type::STRING:
            Variables::instance().setString(name, value);
            break;
    }
}

void tedilang_interpreter_dispatch( std::string line ) {
    if ( KeywordRegistry::instance().run( get_keyword_name(line), line ) ) return;

    if ( is_function(line) ) {
        if ( FunctionRegistry::instance().run( get_function_name(line), get_function_args(line) ) ) return;
    }

    if ( Variables::instance().isDeclaredVariable( line.substr( 0, line.find(' ') ) ) ) {
        tedilang_variables_handler(line);
        return;
    }

    tedilang_exception("Interpreter could not recognize a valid instruction.", line);
}