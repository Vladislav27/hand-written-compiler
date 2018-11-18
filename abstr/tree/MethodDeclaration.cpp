#include "MethodDeclaration.h"

#include "visitors/IVisitor.h"

void NTree::MethodDeclaration::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}
