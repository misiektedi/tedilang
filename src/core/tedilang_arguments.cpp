#include "core/tedilang_arguments.hpp"

#include "version.hpp"

#include <iostream>
#include <string>

void tedilang_argument( std::string arg ) {
    if ( arg == "-v" ) {
        std::cout << TEDILANG_NAME << " " << TEDILANG_VERSION << ".build-" << TEDILANG_BUILD_NUMBER << " (" << TEDILANG_VERSION_STAGE << ")" << std::endl;
        std::cout << TEDILANG_COPYRIGHT << std::endl;

        std::cout << "(build date: " << TEDILANG_BUILD_DATE << ")" << std::endl;
    }

    exit(1);
}