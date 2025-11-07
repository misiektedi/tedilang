#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <array>
#include <algorithm>
#include <cstring>
#include <variant>
#include <ranges>
#include <cctype>

#include "core/tedilang_helpers.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

#include "variables.hpp"

void interpreter(std::string line) {

    if ( KeywordRegistry::instance().run( get_keyword_name(line), line ) ) return;

    if ( is_function(line) ) {
        if ( FunctionRegistry::instance().run( get_function_name(line), get_function_args(line) ) ) return;
    }

    tedilang_exception("Interpreter could not recognize a valid instruction.");

}

int main( int argc, char* argv[] ) {
    std::ifstream file( argv[1] );

    if (!file.is_open()) tedilang_exception("File not exist.");

    std::string line;
    bool main = false;

    while ( getline(file, line, ';') ) {

        if ( line.starts_with("main {") ) {
            main = true;
            line = line.substr(6);
        }

        if ( main == false ) continue;


        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());

        auto view = line
            | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
            | std::views::reverse
            | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
            | std::views::reverse;
        
        std::string line(view.begin(), view.end());

        if ( line.starts_with("#") ) continue;
        if ( line == "}" ) continue;


        interpreter( line );

    }

    file.close();
    return 0;
}