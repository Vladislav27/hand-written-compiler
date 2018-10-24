#pragma once

#include "Common.h"

#include "Expression.h"
#include "INode.h"

namespace NTree {
    class IStatement : public INode {
        IStatement() : INode() {
        }
        IStatement() = default;
    };

    class Statements : public IStatement {
        unique_ptr<vector<unique_ptr<IStatement>>> statements;

        Statements(vector<unique_ptr<IStatement>>* newStatements)
            : IStatement(), statements(newStatements) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class AssignStatement : public IStatement {
        const string lvalue;
        unique_ptr<IExpression> rvalue;

        AssignStatement(const string id, IExpression* expression)
            : IStatement(), lvalue(id), rvalue(expression) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}