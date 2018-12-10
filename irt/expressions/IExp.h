#pragma once

#include <irt/INode.h>

namespace NIRTree {
    interface IExp : public INode {
        IExp(const Location &location = Location()) : INode(location) {
        }

    };
}