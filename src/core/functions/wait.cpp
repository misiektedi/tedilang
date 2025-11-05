#include "register_function.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void func_wait( std::string arg ) {
    int contentInt = stoi(arg);

    std::this_thread::sleep_for(std::chrono::seconds(contentInt));
}

TEDILANG_FUNCTION("wait", func_wait)