#include "Statement.h"

#include "visitors/IVisitor.h"

void NTree::Statements::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::AssignStatement::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

