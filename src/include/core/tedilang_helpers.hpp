#include <iostream>
#include <fstream>
#include <string>
#include <ranges>

bool check_function(std::string line, std::string function_name);

bool is_function(std::string line);

bool is_string(std::string x);

std::string get_function_name(std::string line);
std::string get_function_args(std::string line);
std::string get_keyword_name(std::string line);

std::string remove_qm(std::string text);

std::string string_trim(std::string line);