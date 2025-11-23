#include "register_keyword.hpp"
#include "keyword_registry.hpp"

#include "core/impl/condition.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_parser.hpp"

#include "variables.hpp"

#include <iostream>
#include <sstream>
#include <string>

ReturnType key_while( std::string arg ) {
    arg = string_trim(arg);

    std::string condition = arg.substr( 0, arg.find('{') - 1 );

    std::string content = arg.substr( arg.find_first_of('{') + 1 );
    content = content.substr( 0, content.find_last_of('}') - 1 );
    content = string_trim(content);
    
    while ( get_condition(condition) == true ) {
        std::stringstream ss(content);
        tedilang_parser(ss, true);
    }

    return std::monostate{};
}

TEDILANG_KEYWORD("while", key_while)