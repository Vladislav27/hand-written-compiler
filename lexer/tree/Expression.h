#pragma once

#include "Common.h"

#include "INode.h"

namespace NTree {
    enum EBinaryExprType {
        AND,
        OR,
        LESS,
        PLUS,
        MINUS,
        MULTIPLY
    };

    class IExpression : public INode {
    public:
        explicit IExpression() : INode() {
        }
    };

    class BinaryExpression : public IExpression {
    public:
        EBinaryExprType type;
        unique_ptr<IExpression> left;
        unique_ptr<IExpression> right;

        BinaryExpression(EBinaryExprType expType
            , IExpression* leftExp
            , IExpression* rightExp)
            : IExpression(), type(expType), left(leftExp), right(rightExp) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IntegerLiteralExpression : public IExpression {
    public:
        int value;

        IntegerLiteralExpression(int value)
            : IExpression(), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class BoolLiteralExpression : public IExpression {
    public:
        bool value;

        BoolLiteralExpression(bool value)
            : IExpression(), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IdentifierExpression : public IExpression {
    public:
        const string* identifier;

        IdentifierExpression(const string* identifier)
            : IExpression(), identifier(identifier) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NegateExpression : public IExpression {
    public:
        unique_ptr<IExpression> expression;

        NegateExpression(IExpression* newExpr)
            : IExpression(), expression(newExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}