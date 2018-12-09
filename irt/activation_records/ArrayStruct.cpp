#include "ArrayStruct.h"

#include <irt/NodeTypes.h>

namespace NIRTree {
    IExp* ArrayStruct::GetElement(IExp* base, IExp* elementNumber, const Location& location)
    {
        return new Mem(
                new Binop(Binop::PLUS,
                          new Binop(Binop::PLUS, base, new Const(ElementsOffset, location), location),
                          elementNumber, location), location);

    }

    IExp* ArrayStruct::GetLength(IExp* base, const Location& location)
    {
        return new Mem(base, location);
    }
}
