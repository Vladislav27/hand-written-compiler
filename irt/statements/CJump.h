#pragma once

#include "IStm.h"
#include "Label.h"

#include <irt/expressions/IExp.h>

namespace NIRTree {
    class CJump : public IStm {
    public:
        enum EJumpType {
            EQ = 0,
            NEQ = 1,
            LT = 2
        };

        CJump(const EJumpType jumpType,
              IExp *leftExpr,
              IExp *rightExpr,
              const Label *trueLabel,
              const Location &location)
            : IStm(location), leftExpr(leftExpr), rightExpr(rightExpr),
              trueLabel(trueLabel),
              jumpType(jumpType) {
        }

        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;

        std::unique_ptr<IExp> leftExpr;
        std::unique_ptr<IExp> rightExpr;

        const Label *trueLabel;

        const EJumpType jumpType;
    };
}