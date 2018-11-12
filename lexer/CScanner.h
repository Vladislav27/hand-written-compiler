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
                   Comp::CParser::location_type * location );
        // YY_DECL defined in mc_lexer.l
        // Method body created by flex in mc_lexer.yy.cc

        virtual ~CScanner() {
        };
    private:
        /* yyval ptr */
        Comp::CParser::semantic_type *yylval = nullptr;
    };

} /* end namespace Comp */
