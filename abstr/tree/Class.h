#pragma once

#include "Common.h"

#include "INode.h"
#include "Statement.h"
#include "VarDeclaration.h"
#include "MethodDeclaration.h"
#include "Symbol.h"

namespace NTree {
    class ClassDeclaration : public INode {
    public:
        const Symbol* id;
        const Symbol* extendsId;

        unique_ptr<vector<unique_ptr<VarDeclaration>>> varDeclarations;
        unique_ptr<vector<unique_ptr<MethodDeclaration>>> methodDeclarations;

        ClassDeclaration(const Location& location
                , const NTree::Symbol* name
                , const NTree::Symbol* extends
                , vector<unique_ptr<VarDeclaration>>* vars
                , vector<unique_ptr<MethodDeclaration>>* methods)
                : INode(location), id(name), extendsId(extends), varDeclarations(vars), methodDeclarations(methods) {
        }

        void Accept(IVisitor *visitor) const override;
    };

    class MainClass : public INode {
    public:
        const Symbol* nameId;
        const Symbol* mainArgsId;

        unique_ptr<IStatement> mainStatement;

        MainClass(const Location& location
                , const Symbol* name
                , const Symbol* args
                , IStatement* statement)
                : INode(location), nameId(name), mainArgsId(args), mainStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}