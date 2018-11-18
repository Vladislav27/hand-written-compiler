#pragma once

#include "Common.h"

#include "INode.h"
#include "Type.h"

namespace NTree {
    class VarDeclaration : public INode {
    public:
        Type type;
        const Symbol* id;

        VarDeclaration(const Location& location, const Type& type, const Symbol* id)
            : INode(location), type(type), id(id) {
        }
        void Accept(IVisitor *visitor) const override;
    };
}