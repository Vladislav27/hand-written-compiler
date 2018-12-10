#pragma once

#include "IStm.h"

#include <irt/Label.h>

namespace NIRTree {
    class Jump : public IStm {
    public:
        const Label *label;

        Jump(const Label *label, const Location &location) : IStm(location), label(label) {
        }

        void Accept(IIRVisitor *visitor) const override;
    };
}