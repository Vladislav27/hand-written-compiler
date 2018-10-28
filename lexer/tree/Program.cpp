#include "Program.h"
#include "visitors/IVisitor.h"

namespace NTree {
    void Program::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }
}