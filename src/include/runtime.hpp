#pragma once

#include "core/tedilang_utils.hpp"

#include <functional>
#include <iostream>
#include <variant>
#include <string>
#include <unordered_map>

class Runtime {
    private:
        std::unordered_map<std::string, std::string> config;

    public:
        static Runtime& instance() {
            static Runtime r;
            return r;
        }

        void addConfig(std::string key, std::string value) {
            config[key] = value;
        }

        std::string getConfig(std::string key) {
            return config[key];
        }
};