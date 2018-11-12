#pragma once

#include "Common.h"
#include "Symbol.h"
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

    string binaryTypeToString(EBinaryExprType v);

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

        explicit IntegerLiteralExpression(int value)
            : IExpression(), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class BoolLiteralExpression : public IExpression {
    public:
        bool value;

        explicit BoolLiteralExpression(bool value)
            : IExpression(), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IdentifierExpression : public IExpression {
    public:
        std::unique_ptr<const Symbol> identifier;

        explicit IdentifierExpression(const Symbol* identifier)
            : IExpression(), identifier(identifier) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NegateExpression : public IExpression {
    public:
        unique_ptr<IExpression> expression;

        explicit NegateExpression(IExpression* newExpr)
            : IExpression(), expression(newExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ArrayElementAccessExpression : public IExpression {
    public:
        unique_ptr<IExpression> array;
        unique_ptr<IExpression> index;

        ArrayElementAccessExpression(IExpression* arrayExpr, IExpression* indexExpr)
                : IExpression(), array(arrayExpr), index(indexExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ArrayLengthExpression : public IExpression {
    public:
        unique_ptr<IExpression> array;

        explicit ArrayLengthExpression(IExpression* expression)
                : IExpression(), array(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class MethodCallExpression : public IExpression {
    public:
        unique_ptr<IExpression> object;
        std::unique_ptr<const Symbol> nameId;
        unique_ptr<vector<unique_ptr<IExpression>>> args;

        MethodCallExpression(IExpression* objectExpr
                , const Symbol* name
                , vector<unique_ptr<IExpression>>* argsVector)
                : IExpression(), object(objectExpr), nameId(name), args(argsVector) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ThisExpression : public IExpression {
    public:
        ThisExpression() : IExpression() {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NewIntArrayExpression : public IExpression {
    public:
        unique_ptr<IExpression> size;

        explicit NewIntArrayExpression(IExpression* expression)
                : IExpression(), size(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NewExpression : public IExpression {
    public:
        std::unique_ptr<const Symbol> classId;

        explicit NewExpression(const Symbol* id)
                : IExpression(), classId(id) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}