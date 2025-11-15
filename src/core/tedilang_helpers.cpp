#include <iostream>
#include <fstream>
#include <string>
#include <ranges>

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
std::string get_keyword_name(std::string line) {
    return line.substr(0, line.find(':'));
}

std::string remove_qm(std::string x) {
    if ( x.starts_with('"') && x.ends_with('"') ) {
        return x.substr(1, x.length() - 2 );
    } else {
        return x;
    }
}

std::string string_trim(std::string line) {
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\t'), line.end());

    auto view = line
        | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
        | std::views::reverse
        | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
        | std::views::reverse;
    
    std::string new_line(view.begin(), view.end());
    line = new_line;

    return line;
}