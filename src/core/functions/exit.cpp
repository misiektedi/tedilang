#include "register_function.hpp"
#include "core/tedilang_helpers.hpp"
#include <iostream>

void func_exit( std::string arg ) {
    exit(0);
}

TEDILANG_FUNCTION("exit", func_exit)