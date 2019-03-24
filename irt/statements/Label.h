#pragma once

#include "IStm.h"

#include <irt/Label.h>

namespace NIRTree {
    class LabelStm : public IStm {
    public:
        const Label *label;

        LabelStm(const Label *label, const Location &location) : IStm(location), label(label) {
        }

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;
    };

    typedef std::vector<const Label*> LabelList;
}