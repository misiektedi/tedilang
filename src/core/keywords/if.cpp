#include "register_keyword.hpp"
#include "keyword_registry.hpp"

#include "core/impl/condition.hpp"
#include "core/tedilang_helpers.hpp"

#include "variables.hpp"

#include <iostream>

ReturnType key_if( std::string arg ) {
    std::string lineStriped = arg.substr(3);

    std::string condition = lineStriped.substr( 0, lineStriped.find('{') - 1 );

    std::cout << get_condition(condition) << std::endl;

    return std::monostate{};
}

TEDILANG_KEYWORD("if", key_if)