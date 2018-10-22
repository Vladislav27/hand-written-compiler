#include "VarDeclaration.h"

#include "visitors/IVisitor.h"

namespace NSyntaxTree {
    void VarDeclaration::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }
}