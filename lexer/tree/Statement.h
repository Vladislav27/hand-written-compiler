#pragma once

#include "Common.h"

#include "Expression.h"
#include "INode.h"

namespace NTree {
    class IStatement : public INode {
    public:
        IStatement() : INode() {
        }
    };

    class Statements : public IStatement {
    public:
        unique_ptr<vector<unique_ptr<IStatement>>> statements;

        Statements(vector<unique_ptr<IStatement>>* newStatements)
            : IStatement(), statements(newStatements) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class AssignStatement : public IStatement {
    public:
        const Symbol* lvalue;
        unique_ptr<IExpression> rvalue;

        AssignStatement(const Symbol* id, IExpression* expression)
            : IStatement(), lvalue(id), rvalue(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class IfStatement : public IStatement {
    public:
        unique_ptr<IExpression> condition;

        unique_ptr<IStatement> trueStatement;
        unique_ptr<IStatement> falseStatement;

        IfStatement(IExpression* expression
                , IStatement* newTrueStatement
                , IStatement* newFalseStatement)
                : IStatement(), condition(expression), trueStatement(newTrueStatement), falseStatement(newFalseStatement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class WhileStatement : public IStatement {
    public:
        unique_ptr<IExpression> condition;
        unique_ptr<IStatement> trueStatement;

        WhileStatement(IExpression* expression, IStatement* statement)
                : IStatement(), condition(expression), trueStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class PrintlnStatement : public IStatement {
    public:
        unique_ptr<IExpression> toPrint;

        inline PrintlnStatement(IExpression* expression)
                : IStatement(), toPrint(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class ArrayElementAssignmentStatement : public IStatement {
    public:
        const NTree::Symbol* arrayId;
        unique_ptr<IExpression> index;
        unique_ptr<IExpression> rvalue;

        inline ArrayElementAssignmentStatement(const NTree::Symbol* id
                , IExpression* indexExpr
                , IExpression* rvalueExpr)
                : IStatement(), arrayId(id), index(indexExpr), rvalue(rvalueExpr) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}