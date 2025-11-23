#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"
#include "core/tedilang_interpreter.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

#include "variables.hpp"

void tedilang_parser( std::istream& stream, bool main = false ) {
    std::string line;
    std::string blockContent;
    int blockCount = 0;

    while ( std::getline(stream, line, ';') ) {
        if ( line.starts_with("main {") ) {
            main = true;
            line = line.substr(6);
        }

        if ( main == false ) continue;

        line = string_trim(line);


        if ( line.find('{') != std::string::npos || line.find('}') != std::string::npos || blockCount > 0 ) {
            int bracketCount    = std::count(line.begin(), line.end(), '{');
            blockCount          += bracketCount;

            bracketCount        = std::count(line.begin(), line.end(), '}');
            blockCount          -= bracketCount;

            blockContent        += line;
            blockContent    += ';';
                
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
}