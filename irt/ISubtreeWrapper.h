#pragma once

#include "INode.h"

#include <irt/expressions/IExp.h>

#include <irt/statements/IStm.h>
#include <irt/statements/CJump.h>

namespace NIRTree {
    interface ISubtreeWrapper : public INode {
        explicit ISubtreeWrapper(const Location &location = Location()) : INode(location) {
        }

        virtual ~ISubtreeWrapper() = default;

        virtual IExp* ToExp() = 0;
        virtual IStm* ToStm() = 0;
        virtual IStm* ToConditional(CJump::EJumpType type, const Label *trueLabel) = 0;
    };
}