#pragma once

#include "core/tedilang_utils.hpp"

#include <functional>
#include <iostream>
#include <variant>
#include <string>
#include <unordered_map>

class Variables {
public:
    enum class Type { INT, DOUBLE, STRING, BOOL };

private:
    Type type;
    std::variant<int, double, std::string, bool> data;

    std::unordered_map<std::string, Variables> variables;

public:
    static Variables& instance() {
        static Variables r;
        return r;
    }

    Type getType() const { return type; }
    Type getVarType(const std::string& key) const { return variables.at(key).type; }

    Variables() : type(Type::INT), data(0) {}
    Variables(int v) : type(Type::INT), data(v) {}
    Variables(double v) : type(Type::DOUBLE), data(v) {}
    Variables(const std::string& v) : type(Type::STRING), data(v) {}
    Variables(bool v) : type(Type::BOOL), data(v) {}

    void setInt(const std::string& key, int value) {
        variables[key] = Variables(value);
    }
    void setDouble(const std::string& key, double value) {
        variables[key] = Variables(value);
    }
    void setString(const std::string& key, const std::string& value) {
        variables[key] = Variables(value);
    }
    void setBool(const std::string& key, bool value) {
        variables[key] = Variables(value);
    }

    int getInt(const std::string& key) const {
        return std::get<int>(variables.at(key).data);
    }
    double getDouble(const std::string& key) const {
        return std::get<double>(variables.at(key).data);
    }
    std::string getString(const std::string& key) const {
        return std::get<std::string>(variables.at(key).data);
    }
    bool getBool(const std::string& key) const {
        return std::get<bool>(variables.at(key).data);
    }

    bool isDeclaredVariable(const std::string& key ) const {
        return variables.contains(key);
    }
};