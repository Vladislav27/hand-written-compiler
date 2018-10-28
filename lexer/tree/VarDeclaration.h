#pragma once

#include "Common.h"

#include "INode.h"
#include "Type.h"

namespace NTree {
    class VarDeclaration : public INode {
    public:
        Type type;
        const string* id;

        inline VarDeclaration(const Type& type, const string* id)
            : INode(), type(type), id(id) {
        }
        void Accept(IVisitor *visitor) const override;
    };
}