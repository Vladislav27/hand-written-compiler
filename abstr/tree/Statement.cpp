#include "Statement.h"

#include "visitors/IVisitor.h"

void NTree::Statements::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::AssignStatement::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::IfStatement::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::WhileStatement::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::PrintlnStatement::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::ArrayElementAssignmentStatement::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}


