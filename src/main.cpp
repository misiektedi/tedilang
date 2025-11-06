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
#include "core/impl/calc.hpp"

#include "registry.hpp"
#include "variables.hpp"

void interpreter(std::string line) {

    if ( line.starts_with("let") ) {
        std::array<std::string, 2> types = {"int", "string"};

        std::string lineStriped = line.substr(4);

        std::string type = lineStriped.substr(0, 0 + lineStriped.find(' ') );

        std::string content = lineStriped.substr(1 + type.length());

        size_t pos = content.find('=');

        std::string key = content.substr(0, -1 + pos);
        std::string value = content.substr(pos + 2);
        
        if ( type == "int" ) Variables::instance().setInt( key, calc(value) );
        else if ( type == "string" ) Variables::instance().setString( key, remove_qm(value) );
    }

    if ( is_function(line) ) {
        FunctionRegistry::instance().run( get_function_name(line), get_function_args(line) );
    }

}

int main( int argc, char* argv[] ) {
    std::ifstream file( argv[1] );

    if (!file.is_open()) tedilang_exception("File not exist.");

    std::string line;
    bool main = false;

    while ( getline(file, line, ';') ) {

        if ( line.starts_with("#") ) continue;

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
        

        interpreter( line );

    }

    file.close();
    return 0;
}