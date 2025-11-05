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

std::string function_content(std::string line, int name_length = 0);

std::string remove_qm(std::string text);