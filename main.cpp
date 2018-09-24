#include <fstream>
#include "lexer/CScanner.h"

int main(int argc, char** argv)
{
    ++argv;
    --argc;
    Comp::CScanner* lexer;
    std::ifstream* fin = new std::ifstream;

    if (argc > 0)
    {
        fin->open(argv[0], std::fstream::in);
        lexer = new Comp::CScanner(fin);
    }
    else
    {
        lexer = new Comp::CScanner;
    }

    while(lexer->yylex() != 0) {}
    return 0;
}