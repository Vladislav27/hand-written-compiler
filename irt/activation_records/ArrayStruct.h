#pragma once

#include <irt/expressions/IExp.h>
#include <irt/statements/IStm.h>

namespace NIRTree {

    namespace ArrayStruct {
        // Array format: [Length, 0, 1, ..., n - 1]
        const int ElementsOffset = 1;

        IExp* GetElement(IExp* base, IExp* elementNumber, const Location& location=Location());
        IExp* GetLength(IExp* base, const Location& location=Location());
        IStm* AddReference(IExp* base);
        IStm* RemoveReference(IExp* base);
    }

}