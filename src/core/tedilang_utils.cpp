#include <iostream>
#include <string>

void tedilang_exception(std::string info, std::string content) {
    std::cerr << std::endl << "\e[41m Fatal error \e[0m " << info;

    if ( !content.empty() ) {
        std::cerr << std::endl << "Could not parse: '" << content << "'.";
    }

    std::cerr << std::endl << std::endl;
    exit(0);
}