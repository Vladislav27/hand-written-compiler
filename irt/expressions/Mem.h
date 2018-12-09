#pragma once

#include "IExp.h"

namespace NIRTree {
    class Mem : public IExp {
    public:
        std::unique_ptr<IExp> exp;

        Mem(IExp *_exp, const Location &_location)
            : IExp(_location), exp(_exp) {
        }

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;

        bool IsCommutative() const override { return exp->IsAbsolutelyCommutative(); }
        bool IsAbsolutelyCommutative() const override { return false; }
    };
}