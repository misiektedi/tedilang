#include "register_keyword.hpp"
#include "keyword_registry.hpp"

#include "core/impl/condition.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_interpreter.hpp"

#include "variables.hpp"

#include <iostream>
#include <sstream>
#include <string>

ReturnType key_if( std::string arg ) {
    arg = string_trim(arg);

    std::string condition = arg.substr( 0, arg.find('{') - 1 );

    if ( get_condition(condition) ) {
        std::string content = arg.substr( arg.find_first_of('{') + 1 );
        content = content.substr( 0, content.find_first_of('}') );
        content = string_trim(content);

        std::stringstream ss(content);
        std::string contentLine;

        while (std::getline(ss, contentLine, ';')) {
            tedilang_interpreter_dispatch(contentLine);
        }
    } else {
        std::string content = arg.substr(
            arg.find("else") + arg.substr(arg.find("else")).find('{')
        );
        content = content.substr( 1, content.find_first_of('}') - 1 );
        content = string_trim(content);
        
        std::stringstream ss(content);
        std::string contentLine;

        while (std::getline(ss, contentLine, ';')) {
            tedilang_interpreter_dispatch(contentLine);
        }
    }

    return std::monostate{};
}

TEDILANG_KEYWORD("if", key_if)