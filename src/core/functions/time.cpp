#include "register_function.hpp"
#include "registry.hpp"

#include <iostream>
#include <ctime>

ReturnType func_time( std::string arg ) {
    std::time_t unix_time = std::time(nullptr);

    return 1;
}

TEDILANG_FUNCTION("time", func_time)