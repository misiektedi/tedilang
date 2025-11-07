#include "register_function.hpp"
#include "function_registry.hpp"

#include <iostream>
#include <chrono>
#include <thread>

ReturnType func_wait( std::string arg ) {
    int contentInt = stoi(arg);

    std::this_thread::sleep_for(std::chrono::seconds(contentInt));

    return std::monostate{};
}

TEDILANG_FUNCTION("wait", func_wait)