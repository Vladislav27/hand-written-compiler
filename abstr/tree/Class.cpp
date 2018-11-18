#include "Class.h"
#include "visitors/IVisitor.h"

namespace NTree {
    void ClassDeclaration::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }

    void MainClass::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }
}