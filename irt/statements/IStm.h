#pragma once

#include <irt/INode.h>

namespace NIRTree {
    interface IStm : public NIRTree::INode {
        explicit IStm(const Location &location) : INode(location) {
        }
    };
}