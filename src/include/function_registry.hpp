#pragma once

#include "core/tedilang_utils.hpp"

#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <variant>
#include <vector>

using ReturnType = std::variant<int, double, std::string, bool, std::monostate, long>;

class FunctionRegistry {
public:
    using Function = std::function<ReturnType(const std::vector<std::string>&)>;

    ReturnType result;

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
            return false;
        }

        std::vector<std::string> args;
        std::string buf = "";

        for (char c : arg) {
            if (c == ',') {
                args.push_back(buf);
                buf.clear();
            } else {
                buf += c;
            }
        }

        args.push_back(buf);

        result = it->second(args);

        return true;
    }

private:
    std::unordered_map<std::string, Function> Functions;
};