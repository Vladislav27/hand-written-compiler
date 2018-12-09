#pragma once

#include "IExp.h"

#include <irt/statements/IStm.h>
#include <irt/statements/Seq.h>

namespace NIRTree {
    class ESeq : public IExp {
    public:
        std::unique_ptr<IStm> stm;
        std::unique_ptr<IExp> exp;

        ESeq(IStm *_stm, IExp *_exp, const Location &_location)
                : IExp(_location), stm(_stm), exp(_exp) {
        }

        void Accept(IIRVisitor *visitor) const override;

        void Accept(IIRMutableVisitor *visitor) override;

        void AppendStm(std::unique_ptr<IStm> appendingStm) {
            if (appendingStm) {
                if (!stm) {
                    stm = std::move(appendingStm);
                } else {
                    stm.reset(new Seq(stm.release(), appendingStm.release(), {}));
                }
            }
        }

        bool IsCommutative() const override { return false; }
        bool IsAbsolutelyCommutative() const override { return false; }
    };
}