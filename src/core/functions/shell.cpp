#include "register_function.hpp"
#include "registry.hpp"

#include "core/tedilang_helpers.hpp"
#include <iostream>

ReturnType func_shell( std::string arg ) {
    if ( !is_string(arg) ) exit(1);

    const char* contentChar = remove_qm( arg ).data();

    int result = system(contentChar);

    return result;
}

TEDILANG_FUNCTION("shell", func_shell)