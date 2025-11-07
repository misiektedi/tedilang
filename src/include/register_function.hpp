#pragma once
#include "function_registry.hpp"

struct FunctionRegistrar {
    FunctionRegistrar(const std::string& name, FunctionRegistry::Function func) {
        FunctionRegistry::instance().registerFunction(name, std::move(func));
    }
};

#define TEDILANG_FUNCTION(name, func) \
    static FunctionRegistrar reg_##func(name, func);