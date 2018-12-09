#pragma once

#include "IExp.h"

namespace NIRTree {
    class Unop : public IExp {
    public:
        enum EUnopType {
            NOT = 0,
        };

        Unop(EUnopType type, IExp *expression, const Location &location)
            : IExp(location), type(type), exp(expression) {
        }

        EUnopType type;
        std::unique_ptr<IExp> exp;

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;

        bool IsCommutative() const override { return false; }
        bool IsAbsolutelyCommutative() const override { return false; }
    };
}