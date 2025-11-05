#include <iostream>

void tedilang_exception(std::string info) {
    std::cout << std::endl << "\e[41m Fatal error \e[0m " << info << std::endl << std::endl;
    exit(0);
}