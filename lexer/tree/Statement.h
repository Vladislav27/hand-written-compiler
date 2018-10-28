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
        const string* lvalue;
        unique_ptr<IExpression> rvalue;

        AssignStatement(const string* id, IExpression* expression)
            : IStatement(), lvalue(id), rvalue(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}