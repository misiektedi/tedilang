#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_parser.hpp"

void tedilang_exception(std::string info, std::string content) {
    std::cerr << std::endl << "\e[41m Fatal error \e[0m " << info;

    if ( !content.empty() ) {
        std::cerr << std::endl << "Could not parse: '" << content << "'.";
    }

    std::cerr << std::endl << std::endl;
    exit(0);
}

void tedilang_handle_file(const char* filePath) {
    std::ifstream file( filePath );
    if (!file.is_open()) tedilang_exception("File not exist.");

    tedilang_parser(file);

    file.close();
}