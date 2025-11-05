#pragma once

#include "core/tedilang_utils.hpp"

#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>

class FunctionRegistry {
public:
    using Function = std::function<void(std::string)>;

    static FunctionRegistry& instance() {
        static FunctionRegistry r;
        return r;
    }

    void registerFunction(const std::string& name, Function func) {
        Functions[name] = std::move(func);
    }

    bool run(const std::string& name, std::string arg) {
        auto it = Functions.find(name);
        if (it == Functions.end()) {
            tedilang_exception("Unknown function named '" + name + "'.");
            return false;
        }
        it->second(arg);
        return true;
    }

private:
    std::unordered_map<std::string, Function> Functions;
};