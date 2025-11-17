#include "register_function.hpp"
#include "function_registry.hpp"
#include "variables.hpp"

#include "core/tedilang_helpers.hpp"
#include "core/tedilang_utils.hpp"

#include <iostream>

ReturnType func_output( std::vector<std::string> arg ) {

    std::string argStr = arg[0];

    std::vector<std::string> args;
    std::string buf = "";

    for (char c : argStr) {
        if (c == '~') {
            args.push_back(buf);
            buf.clear();
        } else {
            buf += c;
        }
    }

    args.push_back(buf);
    
    for (std::string str : args) {

        str = string_trim(str);

        if ( is_string(str) ) {
            std::cout << remove_qm( str );
        }
        else if ( is_function(str) )
        {
            std::cout << FunctionRegistry::instance().run( get_function_name(str), get_function_args(str) );
        }
        else if ( Variables::instance().isDeclaredVariable(str) )
        {
            switch (Variables::instance().getVarType(str)) {
                case Variables::Type::INT:
                    std::cout << Variables::instance().getInt(str);
                    break;

                case Variables::Type::STRING:
                    std::cout << Variables::instance().getString(str);
                    break;

                default:
                    tedilang_exception("Nothing to output.");
                    break;
            }
        }
        else
        {
            tedilang_exception("Invalid output() usage.");
        }

    }

    std::cout << std::endl;

    return 0;
}

TEDILANG_FUNCTION("output", func_output)