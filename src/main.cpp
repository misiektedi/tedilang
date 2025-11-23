#include <iostream>
#include <string>

#include "core/tedilang_arguments.hpp"
#include "core/tedilang_utils.hpp"
#include "runtime.hpp"

int main( int argc, char* argv[] ) {
    /**
     * Checks if file is specified
     */
    if ( argc == 1 ) tedilang_exception("Specify file or argument.");
    
    /**
     * Executes special arguments (-v)
     */
    if ( argv[1] && argv[1][0] == '-' ) tedilang_argument( argv[1] );

    /**
     * Adds config to runtime
     */
    std::string entryFilePath = argv[1];
    Runtime::instance().addConfig( "entryFilePath", entryFilePath );
    Runtime::instance().addConfig( "basePath", entryFilePath.substr(0, entryFilePath.find_last_of('/')) );

    /**
     * Sends file path to handler
     */
    tedilang_handle_file( argv[1] );

    return 0;
}