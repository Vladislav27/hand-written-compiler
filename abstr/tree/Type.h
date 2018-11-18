#pragma once

#include "Common.h"
#include "Symbol.h"

namespace NTree {
    enum EType {
        INT,
        BOOL,
        INT_ARRAY,
        CLASS
    };
    
    class Type {
    public:
        EType type = CLASS;
        const Symbol* id{};
        /*
         еcли хочется использовать
         std::unique_ptr<const Symbol> id;
         то неявно удаляется конструктор копирования который используется в VarDeclaration
         */

        ~Type(){
            delete id;
        }

    };
}