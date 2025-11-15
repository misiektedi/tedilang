#include "register_function.hpp"
#include "function_registry.hpp"

#include "core/tedilang_helpers.hpp"
#include <iostream>

ReturnType func_exit( std::vector<std::string> arg ) {
    exit(0);
}

TEDILANG_FUNCTION("exit", func_exit)