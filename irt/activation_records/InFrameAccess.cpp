#include "InFrameAccess.h"
#include <irt/NodeTypes.h>

namespace NIRTree {

    IExp *InFrameAccess::GetExp(Temp *fp, const Location &location) const {
        return new Mem(new Binop(Binop::PLUS, fp, new Const(offset, location), location), location);
    }

    InFrameAccess::InFrameAccess(IAccess::ERecordsType type, int size, int offset)
            : size(size), recordType(type), offset(offset) {
    }


}
