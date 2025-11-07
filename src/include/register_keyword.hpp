#pragma once
#include "keyword_registry.hpp"

struct KeywordRegistrar {
    KeywordRegistrar(const std::string& name, KeywordRegistry::Keyword func) {
        KeywordRegistry::instance().registerFunction(name, std::move(func));
    }
};

#define TEDILANG_KEYWORD(name, func) \
    static KeywordRegistrar reg_##func(name, func);