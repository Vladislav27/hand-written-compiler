#pragma once

#include "Common.h"

namespace NTree {
    class IVisitor;

    class INode {

        INode() = default;

        INode(){}

        virtual void Accept(IVisitor *visitor) const = 0;
        virtual ~INode() = default;
    };
}