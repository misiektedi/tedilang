#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_parser.hpp"

void tedilang_exception(std::string info, std::string content = "");

void tedilang_handle_file(const char* filePath);