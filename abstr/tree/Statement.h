#pragma once

#include "Common.h"

#include "Expression.h"
#include "INode.h"

namespace NTree {
    class IStatement : public INode {
    public:
        IStatement(const Location& location) : INode(location) {
        }
    };

    class Statements : public IStatement {
    public:
        unique_ptr<vector<unique_ptr<IStatement>>> statements;

        Statements(const Location& location, vector<unique_ptr<IStatement>>* newStatements)
            : IStatement(location), statements(newStatements) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class AssignStatement : public IStatement {
    public:
        const Symbol* lvalue;
        unique_ptr<IExpression> rvalue;

        AssignStatement(const Location& location, const Symbol* id, IExpression* expression)
            : IStatement(location), lvalue(id), rvalue(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IfStatement : public IStatement {
    public:
        unique_ptr<IExpression> condition;

        unique_ptr<IStatement> trueStatement;
        unique_ptr<IStatement> falseStatement;

        IfStatement(const Location& location
                , IExpression* expression
                , IStatement* newTrueStatement
                , IStatement* newFalseStatement)
                : IStatement(location), condition(expression), trueStatement(newTrueStatement), falseStatement(newFalseStatement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class WhileStatement : public IStatement {
    public:
        unique_ptr<IExpression> condition;
        unique_ptr<IStatement> trueStatement;

        WhileStatement(const Location& location, IExpression* expression, IStatement* statement)
                : IStatement(location), condition(expression), trueStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class PrintlnStatement : public IStatement {
    public:
        unique_ptr<IExpression> toPrint;

        explicit PrintlnStatement(const Location& location, IExpression* expression)
                : IStatement(location), toPrint(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ArrayElementAssignmentStatement : public IStatement {
    public:
        std::unique_ptr<const Symbol> arrayId;
        unique_ptr<IExpression> index;
        unique_ptr<IExpression> rvalue;

        ArrayElementAssignmentStatement(const Location& location
                , const Symbol* id
                , IExpression* indexExpr
                , IExpression* rvalueExpr)
                : IStatement(location), arrayId(id), index(indexExpr), rvalue(rvalueExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}