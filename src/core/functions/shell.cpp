#include "register_function.hpp"
#include "function_registry.hpp"

#include "core/tedilang_helpers.hpp"
#include <iostream>

ReturnType func_shell( std::vector<std::string> arg ) {

    std::string str = arg[0];

    if ( !is_string(str) ) exit(1);

    const char* contentChar = remove_qm( str ).data();

    int result = system(contentChar);

    return result;
}

TEDILANG_FUNCTION("shell", func_shell)