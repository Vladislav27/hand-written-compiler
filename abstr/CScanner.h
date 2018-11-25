#include <utility>

#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"
#include "StringInterner.h"

// Позже здесь появится парсер от бизона и код надо будет менять

namespace Comp{

    class CScanner : public yyFlexLexer{
    public:
        CScanner(std::istream *in
                , std::shared_ptr<NTree::StringInterner> interner)
                : yyFlexLexer(in), interner(interner)
        {
        };

        //get rid of override virtual function warning
        using FlexLexer::yylex;

        virtual
        int yylex( Comp::CParser::semantic_type * const lval,
                   Comp::CParser::location_type * location );
        // YY_DECL defined in mc_lexer.l
        // Method body created by flex in mc_lexer.yy.cc

        std::shared_ptr<NTree::StringInterner> interner;
    private:
        /* yyval ptr */
        Comp::CParser::semantic_type *yylval = nullptr;
    };

} /* end namespace Comp */
