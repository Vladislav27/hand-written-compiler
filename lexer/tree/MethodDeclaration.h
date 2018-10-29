#pragma once

#include "Common.h"

#include "INode.h"
#include "Statement.h"
#include "Type.h"
#include "VarDeclaration.h"
#include "Symbol.h"


namespace NTree {
    enum EModifier {
        PUBLIC,
        PRIVATE
    };

    struct MethodDeclaration : public INode {
        Type returnType;
        EModifier modifier = PUBLIC;

        const NTree::Symbol* id;
        unique_ptr<vector<unique_ptr<VarDeclaration>>> args;

        unique_ptr<vector<unique_ptr<VarDeclaration>>> localVars;
        unique_ptr<vector<unique_ptr<IStatement>>> statements;
        
        unique_ptr<IExpression> returnExpression;

        MethodDeclaration(Type type
            , const NTree::Symbol* name
            , vector<unique_ptr<VarDeclaration>>* args
            , vector<unique_ptr<VarDeclaration>>* vars
            , vector<unique_ptr<IStatement>>* statements
            , IExpression* expression)
            : INode(), returnType(type), id(name), args(args), localVars(vars), statements(statements), returnExpression(expression) {
            }

        void Accept(IVisitor *visitor) const override;
    };
}