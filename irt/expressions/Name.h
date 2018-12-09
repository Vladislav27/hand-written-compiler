#pragma once

#include "IExp.h"

#include <irt/Label.h>

namespace NIRTree {
    class Name : public IExp {
    public:
        const Label *label;

        explicit Name(const Location &location = Location())
            : IExp(location), label(LabelHolder::GetNextLabel()) {
        }

        Name(const std::string &name, const Location &location)
            : IExp(location),  label(LabelHolder::GetLabel(name)) {
        }

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;

        bool IsCommutative() const override { return true; }
        bool IsAbsolutelyCommutative() const override { return true; }
    };
}