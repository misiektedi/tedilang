#include "register_function.hpp"
#include "function_registry.hpp"

#include <iostream>
#include <ctime>

ReturnType func_time( std::string arg ) {
    long unix_time = static_cast<long>(std::time(nullptr));
    
    return unix_time;
}

TEDILANG_FUNCTION("time", func_time)