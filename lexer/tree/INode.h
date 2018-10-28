#pragma once

#include "Common.h"

namespace NTree {
    class IVisitor;

    class INode {
    public:
        INode(){}

        virtual void Accept(IVisitor *visitor) const = 0;
        virtual ~INode() = default;
    };
}