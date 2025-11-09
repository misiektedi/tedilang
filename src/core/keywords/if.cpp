#include "register_keyword.hpp"
#include "keyword_registry.hpp"

#include "core/impl/condition.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_interpreter.hpp"

#include "variables.hpp"

#include <iostream>

ReturnType key_if( std::string arg ) {
    std::string lineStriped = arg.substr(3);

    std::string lineContent = arg.substr( arg.find('{') + 1 );
    lineContent = string_trim(lineContent);

    std::string condition = lineStriped.substr( 0, lineStriped.find('{') - 1 );

    if ( get_condition(condition) ) {
        tedilang_interpreter_dispatch(lineContent);
    };

    return std::monostate{};
}

TEDILANG_KEYWORD("if", key_if)