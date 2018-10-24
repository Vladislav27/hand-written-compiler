#include "Expression.h"
#include "visitors/IVisitor.h"

void NTree::BinaryExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::IntegerLiteralExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::BoolLiteralExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::IdentifierExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::NegateExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}
