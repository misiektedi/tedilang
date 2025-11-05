#include "register_function.hpp"
#include "core/tedilang_helpers.hpp"
#include <iostream>

void func_shell( std::string arg ) {
    if ( !is_string(arg) ) exit(1);

    const char* contentChar = remove_qm( arg ).data();

    int result = system(contentChar);
}

TEDILANG_FUNCTION("shell", func_shell)