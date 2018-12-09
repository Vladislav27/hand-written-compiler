#pragma once

#include <irt/List.h>

namespace NIRTree {
    class Call : public IExp {
    public:
        std::unique_ptr<IExp> funcExp;
        std::unique_ptr<ExpList> args;

        Call(IExp *_funcExp, ExpList *_args, const Location &_location)
            : IExp(_location), funcExp(_funcExp), args(_args) {
        }
            
        void Accept(IIRVisitor *visitor) const override;
        void Accept(IIRMutableVisitor *visitor) override;
        bool IsCommutative() const override { return false; }
        bool IsAbsolutelyCommutative() const override { return false; }
    };
}