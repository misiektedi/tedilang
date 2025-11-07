#pragma once

#include "core/tedilang_utils.hpp"

#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <variant>

using ReturnType = std::variant<int, double, std::string, bool, std::monostate>;

class KeywordRegistry {
public:
    using Keyword = std::function<ReturnType(const std::string&)>;

    static KeywordRegistry& instance() {
        static KeywordRegistry r;
        return r;
    }

    void registerFunction(const std::string& name, Keyword func) {
        Keywords[name] = std::move(func);
    }

    bool run(const std::string& name, std::string arg) {
        auto it = Keywords.find(name);
        if (it == Keywords.end()) {
            return false;
        }
        it->second(arg);
        return true;
    }

private:
    std::unordered_map<std::string, Keyword> Keywords;
};