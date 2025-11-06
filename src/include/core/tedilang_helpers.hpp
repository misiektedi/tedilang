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

bool check_function(std::string line, std::string function_name);

bool is_function(std::string line);

bool is_string(std::string x);

std::string get_function_name(std::string line);
std::string get_function_args(std::string line);

std::string remove_qm(std::string text);