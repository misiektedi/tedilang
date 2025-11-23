#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"
#include "core/tedilang_variables.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

#include "variables.hpp"

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