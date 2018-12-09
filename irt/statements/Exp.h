#pragma once

#include "IStm.h"

#include <irt/expressions/IExp.h>

namespace NIRTree {
    class Exp : public IStm {
    public:
        std::unique_ptr<IExp> exp;

        Exp(IExp *expr, const Location &location)
            : IStm(location), exp(expr) {
        }

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;
    };
}