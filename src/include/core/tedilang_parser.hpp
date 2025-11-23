#include <iostream>
#include <fstream>
#include <string>

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_arguments.hpp"
#include "core/tedilang_interpreter.hpp"

#include "function_registry.hpp"
#include "keyword_registry.hpp"

#include "variables.hpp"

void tedilang_parser( std::istream& stream, bool main = false );