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
        const Symbol* id;

//        Type& operator=(Type& t)
//        {
//            type = t.type;
//            id = t.id;
//        }
    };
}