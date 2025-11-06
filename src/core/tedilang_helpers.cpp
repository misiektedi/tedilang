#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <array>
#include <algorithm>
#include <cstring>
#include <variant>
#include <ranges>
#include <cctype>

bool check_function(std::string line, std::string function_name) {
    if ( line.starts_with(function_name + "(") && line.ends_with(")") ) return true;

    return false;
}

bool is_function(std::string line) {
    if ( line.find('(') != std::string::npos && line.ends_with(")") ) return true;

    return false;
}

bool is_string(std::string x) {
    if ( x.starts_with('"') && x.ends_with('"') ) return true;

    return false;
}

std::string get_function_name(std::string line) {
    size_t nameLength = line.find_first_of('(');

    return line.substr(0, nameLength);
}
std::string get_function_args(std::string line) {
    size_t nameLength = line.find_first_of('(');

    return line.substr(nameLength + 1, line.length() - nameLength - 2 );
}

std::string remove_qm(std::string text) {
    return text.substr(1, text.length() - 2 );
}