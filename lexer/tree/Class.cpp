#include "Class.h"
#include "visitors/IVisitor.h"

namespace NTree {

    void MainClass::Accept(IVisitor *visitor) const {
        visitor->Visit(this);
    }
}