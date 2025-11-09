#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

void tedilang_interpreter_dispatch( std::string line );