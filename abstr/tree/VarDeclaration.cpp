#include "VarDeclaration.h"

#include "visitors/IVisitor.h"

namespace NTree {
    void NTree::VarDeclaration::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }
}