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

void NTree::ArrayElementAccessExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::ArrayLengthExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::MethodCallExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::ThisExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::NewIntArrayExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

void NTree::NewExpression::Accept(NTree::IVisitor *visitor) const {
    visitor->Visit(this);
}

std::string NTree::binaryTypeToString(NTree::EBinaryExprType v)
{
    switch (v)
    {
        case EBinaryExprType::AND:   return "AND";
        case EBinaryExprType::OR:   return "OR";
        case EBinaryExprType::LESS: return "LESS";
        case EBinaryExprType::PLUS: return "PLUS";
        case EBinaryExprType::MINUS: return "MINUS";
        case EBinaryExprType::MULTIPLY: return "MULTIPLY";
        default:      return "[Unknown]";
    }
}
