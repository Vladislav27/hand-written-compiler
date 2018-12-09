#pragma once

#include "IExp.h"

namespace NIRTree {
    class Const : public IExp {
    public:
        const int value;

        Const(int _value, const Location &_location)
            : IExp(_location), value(_value) {
        }

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;
        bool IsCommutative() const override { return true; }
        bool IsAbsolutelyCommutative() const override { return true; }
    };
}