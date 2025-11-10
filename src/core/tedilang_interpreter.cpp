#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

void tedilang_interpreter_dispatch( std::string line ) {
    
    if ( KeywordRegistry::instance().run( get_keyword_name(line), line ) ) return;

    if ( is_function(line) ) {
        if ( FunctionRegistry::instance().run( get_function_name(line), get_function_args(line) ) ) return;
    }

    tedilang_exception("Interpreter could not recognize a valid instruction.");

}