#pragma once

#include "Common.h"

namespace NTree {
    enum EType {
        INT,
        BOOL,
        INT_ARRAY,
        CLASS
    };
    
    struct Type {
        EType type = CLASS;
        const string id;
    };
}