#include "register_keyword.hpp"
#include "keyword_registry.hpp"

#include "core/impl/condition.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_utils.hpp"

#include "variables.hpp"
#include "runtime.hpp"

#include <iostream>
#include <string>

ReturnType key_include( std::string arg ) {
    arg = string_trim(arg);

    std::string basePath = Runtime::instance().getConfig("basePath");
    std::string filePath = basePath + "/" + remove_qm(arg) + ".tedi";

    tedilang_handle_file( filePath.c_str() );

    return std::monostate{};
}

TEDILANG_KEYWORD("include", key_include)