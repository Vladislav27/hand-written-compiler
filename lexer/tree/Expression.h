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
        explicit IExpression() : INode() {
        }
        IExpression() = default;
    };

    class BinaryExpression : public IExpression {
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
        int value;

        IntegerLiteralExpression(int value)
            : IExpression(), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class BoolLiteralExpression : public IExpression {
        bool value;

        BoolLiteralExpression(bool value)
            : IExpression(), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IdentifierExpression : public IExpression {
        const string identifier;

        IdentifierExpression(const string identifier)
            : IExpression(), identifier(identifier) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NegateExpression : public IExpression {
        unique_ptr<IExpression> expression;

        NegateExpression(IExpression* newExpr)
            : IExpression(), expression(newExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}