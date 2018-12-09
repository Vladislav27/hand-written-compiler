#pragma once

#include "IStm.h"

#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Move : public IStm {
    public:
        std::unique_ptr<IExp> dst;
        std::unique_ptr<IExp> src;

        Move(IExp *dst, IExp *src, const Location &location)
            : IStm(location), dst(dst), src(src) {
        }

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;
    };
}