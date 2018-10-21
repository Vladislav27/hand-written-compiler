#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"

// Позже здесь появится парсер от бизона и код надо будет менять

namespace Comp{

    class CScanner : public yyFlexLexer{
    public:
        CScanner(std::istream *in) : yyFlexLexer(in)
        {
        };

        //get rid of override virtual function warning
        using FlexLexer::yylex;

        virtual
        int yylex( Comp::CParser::semantic_type * const lval,
                   Comp::CParser::location_type *location );
        // YY_DECL defined in mc_lexer.l
        // Method body created by flex in mc_lexer.yy.cc

        virtual ~CScanner() {
        };
    private:
        /* yyval ptr */
        Comp::CParser::semantic_type *yylval = nullptr;
    };

    class LineHandler {
    public:
        unsigned int getPosition(unsigned int step)
        {
            int old = position;
            position += step;
            return old;
        }
        void refreshValues()
        {
            position = 1;
            currentLine++;
        }
        unsigned int getLine()
        {
            return currentLine;
        }

    private:
        unsigned int position = 1;
        unsigned int currentLine = 1;
    };

} /* end namespace Comp */
