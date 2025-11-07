#include "register_keyword.hpp"
#include "keyword_registry.hpp"

#include "core/impl/calc.hpp"
#include "core/tedilang_helpers.hpp"

#include "variables.hpp"

#include <iostream>

ReturnType key_let( std::string arg ) {
    std::array<std::string, 2> types = {"int", "string"};

    std::string lineStriped = arg.substr(4);

    std::string type = lineStriped.substr(0, 0 + lineStriped.find(' ') );

    std::string content = lineStriped.substr(1 + type.length());

    size_t pos = content.find('=');

    std::string key = content.substr(0, -1 + pos);
    std::string value = content.substr(pos + 2);
    
    if ( type == "int" ) Variables::instance().setInt( key, calc(value) );
    else if ( type == "string" ) Variables::instance().setString( key, remove_qm(value) );

    return std::monostate{};
}

TEDILANG_KEYWORD("let", key_let)