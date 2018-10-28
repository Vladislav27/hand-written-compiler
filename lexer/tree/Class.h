#pragma once

#include "Common.h"

#include "INode.h"
#include "Statement.h"
#include "VarDeclaration.h"
#include "Symbol.h"

namespace NTree {

    class MainClass : public INode {
    public:
        const Symbol* nameId;
        const Symbol* mainArgsId;

        unique_ptr<IStatement> mainStatement;

        MainClass(const Symbol* name
            , const Symbol* args
            , IStatement* statement)
            : INode(), nameId(name), mainArgsId(args), mainStatement(statement) {
        }

        void Accept(IVisitor *visitor) const override;
    };
}