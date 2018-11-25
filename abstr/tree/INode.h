#pragma once

#include "Common.h"

namespace NTree {
    class IVisitor;

    class INode {
    public:
        Location location{};

        INode() = default;

        explicit INode(const Location& location) : location(location) {
        }

        virtual void Accept(IVisitor *visitor) const = 0;
        virtual ~INode() = default;
    };
}