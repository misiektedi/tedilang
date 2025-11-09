#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"
#include "core/tedilang_interpreter.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

#include "variables.hpp"

int main( int argc, char* argv[] ) {
    if ( argv[1][0] == '-' ) tedilang_argument(argv[1]);

    std::ifstream file( argv[1] );

    if (!file.is_open()) tedilang_exception("File not exist.");

    std::string line;
    std::string blockContent;

    bool main = false;
    bool inBlock = false;

    while ( getline(file, line, ';') ) {

        if ( line.starts_with("main {") ) {
            main = true;
            line = line.substr(6);
        }

        if ( main == false ) continue;

        line = string_trim(line);


        if (line.find('{') != std::string::npos) {
            inBlock = true;
            blockContent += line + ';';
            continue;
        }
        else if (inBlock && line.find('}') == std::string::npos) {
            blockContent += line + ';'; continue;
        }
        else if (inBlock && line.find('}') != std::string::npos) {
            inBlock = false;
            tedilang_interpreter_dispatch( blockContent );
            continue;
        }


        if ( line.starts_with("#") ) continue;
        if ( line == "}" ) continue;


        tedilang_interpreter_dispatch( line );

    }

    file.close();
    return 0;
}