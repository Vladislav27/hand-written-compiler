#pragma once

#include "Common.h"

#include "INode.h"
#include "Statement.h"
#include "VarDeclaration.h"

namespace NTree {

    class MainClass : public INode {
    public:
        const string* nameId;
        const string* mainArgsId;

        unique_ptr<IStatement> mainStatement;

        inline MainClass(string* name
            , string* args
            , IStatement* statement)
            : INode(), nameId(name), mainArgsId(args), mainStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}