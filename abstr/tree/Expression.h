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
        explicit IExpression(const Location& location) : INode(location) {
        }
    };

    class BinaryExpression : public IExpression {
    public:
        EBinaryExprType type;
        unique_ptr<IExpression> left;
        unique_ptr<IExpression> right;

        BinaryExpression(const Location& location
                , EBinaryExprType expType
                , IExpression* leftExp
                , IExpression* rightExp)
                : IExpression(location), type(expType), left(leftExp), right(rightExp) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IntegerLiteralExpression : public IExpression {
    public:
        int value;

        IntegerLiteralExpression(const Location& location, int value)
            : IExpression(location), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class BoolLiteralExpression : public IExpression {
    public:
        bool value;

        explicit BoolLiteralExpression(const Location& location, bool value)
            : IExpression(location), value(value) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IdentifierExpression : public IExpression {
    public:
        const Symbol* identifier;

        explicit IdentifierExpression(const Location& location, const Symbol* identifier)
            : IExpression(location), identifier(identifier) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NegateExpression : public IExpression {
    public:
        unique_ptr<IExpression> expression;

        explicit NegateExpression(const Location& location, IExpression* newExpr)
            : IExpression(location), expression(newExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ArrayElementAccessExpression : public IExpression {
    public:
        unique_ptr<IExpression> array;
        unique_ptr<IExpression> index;

        ArrayElementAccessExpression(const Location& location, IExpression* arrayExpr, IExpression* indexExpr)
                : IExpression(location), array(arrayExpr), index(indexExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ArrayLengthExpression : public IExpression {
    public:
        unique_ptr<IExpression> array;

        ArrayLengthExpression(const Location& location, IExpression* expression)
                : IExpression(location), array(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class MethodCallExpression : public IExpression {
    public:
        unique_ptr<IExpression> object;
        const Symbol* nameId;
        unique_ptr<vector<unique_ptr<IExpression>>> args;

        MethodCallExpression(const Location& location
                , IExpression* objectExpr
                , const Symbol* name
                , vector<unique_ptr<IExpression>>* argsVector)
                : IExpression(location), object(objectExpr), nameId(name), args(argsVector) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ThisExpression : public IExpression {
    public:
        explicit ThisExpression(const Location& location)
            : IExpression(location) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NewIntArrayExpression : public IExpression {
    public:
        unique_ptr<IExpression> size;

        NewIntArrayExpression(const Location& location, IExpression* expression)
                : IExpression(location), size(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class NewExpression : public IExpression {
    public:
        const Symbol* classId;

        NewExpression(const Location& location, const Symbol* id)
                : IExpression(location), classId(id) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}