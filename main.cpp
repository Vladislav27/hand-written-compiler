#include <fstream>
#include "abstr/CDriver.h"

int main(int argc, char** argv)
{

    if (argc > 0)
    {
        Comp::CDriver driver;
        driver.parse( argv[1] );

        std::ofstream fout;
        fout.open("graph.gv");
        driver.print(fout);
        fout.close();
    }
    else
    {
        return ( EXIT_FAILURE );
    }
    return 0;
}