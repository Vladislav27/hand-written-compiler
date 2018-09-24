#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Позже здесь появится парсер от бизона и код надо будет менять

namespace Comp{

    class CScanner : public yyFlexLexer{
    public:
        CScanner() : yyFlexLexer()
        {
        };
        CScanner(std::istream *in) : yyFlexLexer(in)
        {
        };
        virtual ~CScanner() {
        };
    };

} /* end namespace Comp */
