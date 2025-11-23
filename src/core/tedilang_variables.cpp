#include <iostream>
#include <string>

#include "function_registry.hpp"

#include "variables.hpp"
#include "core/impl/calc.hpp"

void tedilang_variables_handler( std::string x ) {
    char symbol             = x[x.find('=') - 1];

    if ( symbol == '+' || symbol == '-' ) {
        size_t pos          = x.find('=');

        std::string name    = x.substr(0, pos - 2);
        std::string value   = x.substr(pos + 1, x.length());

        name                = string_trim(name);
        if (symbol == '+')          value = name + "+" + string_trim(value);
        else if (symbol == '-')     value = name + "-" + string_trim(value);

        Variables::instance().setInt(name, calc(value));

    } else
    {
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
}