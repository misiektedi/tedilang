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
    if ( argc == 1 ) tedilang_exception("Specify file or argument.");
    
    if ( argv[1] && argv[1][0] == '-' ) tedilang_argument(argv[1]);

    std::ifstream file( argv[1] );

    if (!file.is_open()) tedilang_exception("File not exist.");

    std::string line;
    std::string blockContent;
    bool main = false;
    int blockCount = 0;

    while ( getline(file, line, ';') ) {

        if ( line.starts_with("main {") ) {
            main = true;
            line = line.substr(6);
        }

        if ( main == false ) continue;

        line = string_trim(line);




        if ( line.find('{') != std::string::npos || line.find('}') != std::string::npos ) {
            int bracketCount = std::count(line.begin(), line.end(), '{');
            blockCount += bracketCount;

            bracketCount = std::count(line.begin(), line.end(), '}');
            blockCount -= bracketCount;

            blockContent += line;
            if (!line.ends_with('}')) {
                blockContent += ';';
            }

            if (blockCount == 0 && line == "}") {
                tedilang_interpreter_dispatch( blockContent );
                blockContent = "";
            };

            continue;
        }




        if ( line.starts_with("#") ) continue;
        if ( line == "}" ) continue;


        tedilang_interpreter_dispatch( line );

    }

    file.close();
    return 0;
}