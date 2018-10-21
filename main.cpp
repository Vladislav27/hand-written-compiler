#include <fstream>
#include "lexer/CDriver.h"

int main(int argc, char** argv)
{

    if (argc > 0)
    {
        Comp::CDriver driver;
        driver.parse( argv[1] );
        driver.print( std::cout ) << "\n";
    }
    else
    {
        return ( EXIT_FAILURE );
    }
    return 0;
}